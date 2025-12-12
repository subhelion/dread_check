#include <zed/app.h>
#include <zed/app/system.h>
#include <zed/app/audio.h>
#include <zed/platform/audio/miniaudio.h>

namespace app_audio_internal {
	ma_device device;

	// ma_vfs    vfs;

	zed_file  file;
	zed_sound *sound_current;

	zed_sound *sounds[256] = {};
	int sounds_i;

	// todo

	handle wav_buffer = malloc( 0xC0000 );
};

uint32_t mix_pcm_f32( ma_decoder *decoder, float *output_f32, uint32_t frame_count, float volume = 1.0 ) {
	float temp[4096];

	#define CHANNEL_COUNT 2
	ma_uint32 tempCapInFrames = ma_countof(temp) / CHANNEL_COUNT;
    ma_uint32 totalFramesRead = 0;

    while (totalFramesRead < frame_count) {
        ma_uint32 iSample;
        ma_uint32 framesReadThisIteration;
        ma_uint32 totalFramesRemaining = frame_count - totalFramesRead;
        ma_uint32 framesToReadThisIteration = tempCapInFrames;
        if (framesToReadThisIteration > totalFramesRemaining) {
            framesToReadThisIteration = totalFramesRemaining;
        }

        framesReadThisIteration = (ma_uint32)ma_decoder_read_pcm_frames( decoder, temp, framesToReadThisIteration);
        if (framesReadThisIteration == 0) {
            break;
        }

        /* Mix the frames together. */
        for (iSample = 0; iSample < framesReadThisIteration*CHANNEL_COUNT; ++iSample) {
            output_f32[totalFramesRead*CHANNEL_COUNT + iSample] += temp[iSample] * volume;
        }

        totalFramesRead += framesReadThisIteration;

        if (framesReadThisIteration < framesToReadThisIteration) {
            break;  /* Reached EOF. */
        }
    }

    return totalFramesRead;
}

void on_audio( ma_device *device, void *output, const void *input, uint32_t frame_count ) {
	using namespace app_audio_internal;

	// if ( sound_current == 0 ) return;
    // ma_decoder_read_pcm_frames( &sound_current->decoder, output, frame_count );

	float *output_f32 = (float *)output;

	// todo
    // MA_ASSERT(pDevice->playback.format == SAMPLE_FORMAT);

    for ( int i = 0; i < 256; i++ ) {
		if ( sounds[i] == 0 ) break;
        if ( sounds[i]->is_playing ) {
            uint32_t framesRead = mix_pcm_f32( &( sounds[i]->decoder ), output_f32, frame_count, sounds[i]->volume );
            if ( framesRead < frame_count ) sounds[i]->is_playing = false;
        }
    }
}

void app_audio_init() {
	using namespace app_audio_internal;

	ma_device_config config  = ma_device_config_init( ma_device_type_playback );
    config.playback.format   = ma_format_f32;
    config.playback.channels = 2;
    config.sampleRate        = 48000;
    config.dataCallback      = on_audio;
    config.pUserData         = 0;

	ma_device_init( 0, &config, &device );
    ma_device_start( &device );
	// ma_device_set_master_volume( &device, 0.2 );
}

void app_audio_exit() {
	using namespace app_audio_internal;

	ma_device_uninit( &device );
}

//

// size_t on_read( ma_decoder *decoder, handle buffer, size_t bytes_to_read ) {
// 	using namespace app_audio_internal;
//
// 	return app_system_fread( buffer, bytes_to_read, 1, file );
// }
//
// ma_bool32 on_seek( ma_decoder* pDecoder, int64_t offset, ma_seek_origin origin ) {
// 	using namespace app_audio_internal;
//
// 	// todo handle other origins
// 	return app_system_fseek( file, offset );
// }

//

void zed_load_sound( zed_sound &sound, string path ) {
	using namespace app_audio_internal;

	ma_decoder_config config = ma_decoder_config_init( ma_format_f32, 2, 48000 );
	config.encodingFormat    = ma_encoding_format_wav;

// 	file = app_system_fopen( path );
// 	handle wav_buffer_next = (char *)wav_buffer + PHYSFS_fileLength( file.stream );
//
// 	PHYSFS_read( file.stream, wav_buffer, 1, PHYSFS_fileLength( file.stream ) );
// 	ma_decoder_init_memory( wav_buffer, PHYSFS_fileLength( file.stream ), &config, &sound.decoder );
//
// 	app_system_fclose( file );
// 	wav_buffer = wav_buffer_next;

	ma_decoder_init_file( path, &config, &sound.decoder );

	sounds[ sounds_i++ ] = &sound;
}

void zed_load_sound( zed_sound &sound, int id ) {
	using namespace app_audio_internal;

	ma_decoder_config config = ma_decoder_config_init( ma_format_f32, 2, 48000 );
	config.encodingFormat    = ma_encoding_format_wav;

	handle resource_data = app_system_resource_data( id );
	int    resource_size = app_system_resource_size( id );
	ma_decoder_init_memory( resource_data, resource_size, &config, &sound.decoder );

	sounds[ sounds_i++ ] = &sound;
}

void zed_play_sound( zed_sound &sound, float volume_db, float pitch ) {
	using namespace app_audio_internal;

	ma_decoder_seek_to_pcm_frame( &sound.decoder, 0 );
	sound_current = &sound;

	sound.is_playing = true;
	sound.volume = ma_gain_db_to_factor( volume_db );
}
