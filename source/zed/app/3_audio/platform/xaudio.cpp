#include <zed/app.h>
#include <zed/app/audio.h>
#include <zed/platform/audio/xaudio.h>

// debug
#include <comdef.h>

void log_hresult( HRESULT result ) {
	_com_error err(result);
	LPCTSTR errMsg = err.ErrorMessage();
	// std::cout << errMsg << "\n";
}

void app_audio_init() {
	// std::cout << "Audio  - Initializing\n";

	HRESULT result;

	// std::cout << "Audio  - Creating device - ";
	result = XAudio2Create( &app.audio.device, 0, XAUDIO2_DEFAULT_PROCESSOR );
	log_hresult( result );

	// std::cout << "Audio  - Creating mastering voice - ";
	result = app.audio.device->CreateMasteringVoice( &app.audio.mv );
	log_hresult( result );

	XAUDIO2_DEBUG_CONFIGURATION xdc;

	xdc                 = {};
	xdc.TraceMask       = XAUDIO2_LOG_WARNINGS | XAUDIO2_LOG_DETAIL | XAUDIO2_LOG_FUNC_CALLS;
	xdc.BreakMask       = XAUDIO2_LOG_WARNINGS;
	xdc.LogThreadID     = true;
	xdc.LogFileline     = true;
	xdc.LogFunctionName = true;
	xdc.LogTiming       = true;

	app.audio.device->SetDebugConfiguration( &xdc, 0 );
}

void app_audio_exit() {
	//
}

#ifdef _XBOX
	// Big-Endian
	#define fourccRIFF 'RIFF'
	#define fourccDATA 'data'
	#define fourccFMT  'fmt '
	#define fourccWAVE 'WAVE'
	#define fourccXWMA 'XWMA'
	#define fourccDPDS 'dpds'
#else
	// Little-Endian
	#define fourccRIFF 'FFIR'
	#define fourccDATA 'atad'
	#define fourccFMT  ' tmf'
	#define fourccWAVE 'EVAW'
	#define fourccXWMA 'AMWX'
	#define fourccDPDS 'sdpd'
#endif

HRESULT FindChunk( HANDLE hFile, uint32_t fourcc, uint32_t *chunk_size, uint32_t *chunk_offset ) {
	HRESULT hr = S_OK;
	if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, 0, NULL, FILE_BEGIN ) )
		return HRESULT_FROM_WIN32( GetLastError() );

	uint32_t dwChunkType;
	uint32_t dwChunkDataSize;
	uint32_t dwRIFFDataSize = 0;
	uint32_t dwFileType;
	uint32_t bytesRead = 0;
	uint32_t dwOffset = 0;

	while ( hr == S_OK ) {
		DWORD dwRead;
		if( 0 == ReadFile( hFile, &dwChunkType, sizeof(uint32_t), &dwRead, NULL ) )
			hr = HRESULT_FROM_WIN32( GetLastError() );

		if( 0 == ReadFile( hFile, &dwChunkDataSize, sizeof(uint32_t), &dwRead, NULL ) )
			hr = HRESULT_FROM_WIN32( GetLastError() );

		switch ( dwChunkType ) {
			case fourccRIFF: {
				dwRIFFDataSize = dwChunkDataSize;
				dwChunkDataSize = 4;
				if( 0 == ReadFile( hFile, &dwFileType, sizeof(uint32_t), &dwRead, NULL ) )
					hr = HRESULT_FROM_WIN32( GetLastError() );
				break;
			}

			default: {
				if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, dwChunkDataSize, NULL, FILE_CURRENT ) )
				return HRESULT_FROM_WIN32( GetLastError() );
			}
		}

		dwOffset += sizeof(uint32_t) * 2;

		if ( dwChunkType == fourcc ) {
			*chunk_size   = dwChunkDataSize;
			*chunk_offset = dwOffset;
			return S_OK;
		}

		dwOffset += dwChunkDataSize;

		if ( bytesRead >= dwRIFFDataSize ) return S_FALSE;

	}

	return S_OK;
}

HRESULT ReadChunkData( handle hFile, handle buffer, uint32_t buffersize, uint32_t bufferoffset ) {
	HRESULT hr = S_OK;
	if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, bufferoffset, NULL, FILE_BEGIN ) )
		return HRESULT_FROM_WIN32( GetLastError() );
	DWORD dwRead;
	if( 0 == ReadFile( hFile, buffer, buffersize, &dwRead, NULL ) )
		hr = HRESULT_FROM_WIN32( GetLastError() );
	return hr;
}

//

void zed_load_sound( zed_sound &sound, string path ) {
	WAVEFORMATEXTENSIBLE wfx    = {};
	XAUDIO2_BUFFER       buffer = {};

	handle file = CreateFileA( path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0 );

	uint32_t chunk_size;
	uint32_t chunk_offset;

	// check the file type, should be fourccWAVE or 'XWMA'
	FindChunk( file, fourccRIFF, &chunk_size, &chunk_offset );

	DWORD filetype;
	ReadChunkData( file, &filetype, sizeof(DWORD), chunk_offset );
	// if (filetype != fourccWAVE)
	// 	return S_FALSE;

	FindChunk    ( file, fourccFMT, &chunk_size, &chunk_offset );
	ReadChunkData( file, &wfx,       chunk_size,  chunk_offset );

	//fill out the audio data buffer with the contents of the fourccDATA chunk
	FindChunk( file, fourccDATA, &chunk_size, &chunk_offset );
	byte *pDataBuffer = new byte[chunk_size];
	ReadChunkData( file, pDataBuffer, chunk_size, chunk_offset );

	buffer.AudioBytes = chunk_size;  //size of the audio buffer in bytes
	buffer.pAudioData = pDataBuffer;  //buffer containing audio data
	buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer

	sound.wfx = wfx;
	sound.buffer = buffer;

	app.audio.device->CreateSourceVoice( &(sound.pSourceVoice), (WAVEFORMATEX *)&wfx );
}

void zed_play_sound( zed_sound &sound, float volume, float pitch ) {
	sound.pSourceVoice->SetVolume        ( XAudio2DecibelsToAmplitudeRatio ( volume ) );
	sound.pSourceVoice->SetFrequencyRatio( XAudio2SemitonesToFrequencyRatio( pitch  ) );

	sound.pSourceVoice->Stop();
	sound.pSourceVoice->FlushSourceBuffers();
	sound.pSourceVoice->SubmitSourceBuffer( &(sound.buffer) );
	sound.pSourceVoice->Start( 0 );
}
