#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/platform/d3d11.h>

void app_graphics_depth_stencil_buffer_and_view( size2, ID3D11Texture2D **, ID3D11DepthStencilView **, ID3D11DepthStencilView ** );

void zed_canvas_new( zed_canvas &canvas, int canvas_width, int canvas_height ) {
	canvas.size = { canvas_width, canvas_height };

	D3D11_TEXTURE2D_DESC td = {};
	td.Width                = canvas_width;
	td.Height               = canvas_height;
	td.MipLevels            = 1;
	td.ArraySize            = 1;
	td.Format               = DXGI_FORMAT_R8G8B8A8_UNORM;
	td.SampleDesc.Count     = 1;
	td.Usage                = D3D11_USAGE_DEFAULT;
	td.BindFlags            = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags       = 0;
	td.MiscFlags            = 0;

	ID3D11Texture2D *t;
	app.graphics.device->CreateTexture2D( &td, 0, &t );

	D3D11_RENDER_TARGET_VIEW_DESC rtvd = {};
	rtvd.Format                        = td.Format;
	rtvd.ViewDimension                 = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvd.Texture2D.MipSlice            = 0;

	app.graphics.device->CreateRenderTargetView( t, &rtvd, &canvas.rtv );

	t->Release();

	D3D11_SHADER_RESOURCE_VIEW_DESC srvd = {};
	srvd.Format                          = td.Format;
	srvd.ViewDimension                   = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MostDetailedMip       = 0;
	srvd.Texture2D.MipLevels             = 1;

	app.graphics.device->CreateShaderResourceView( t, &srvd, &canvas.srv );

	app_graphics_depth_stencil_buffer_and_view( canvas.size, &canvas.dsb, &canvas.dsv, &canvas.dsvro );

	D3D11_SHADER_RESOURCE_VIEW_DESC dsrvd = {};
	// dsrvd.Format                          = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsrvd.Format                          = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	dsrvd.ViewDimension                   = D3D11_SRV_DIMENSION_TEXTURE2D;
	dsrvd.Texture2D.MostDetailedMip       = 0;
	dsrvd.Texture2D.MipLevels             = 1;

	app.graphics.device->CreateShaderResourceView( canvas.dsb, &dsrvd, &canvas.dsrv );
}

void zed_use_canvas_2d( zed_canvas &canvas ) {
	app.graphics.device_context->PSSetShaderResources( 0, 1, &canvas.srv );
}

void zed_use_canvas_3d( zed_canvas &canvas ) {
	app.graphics.device_context->PSSetShaderResources( 0, 2, &canvas.srv );
}

void zed_canvas_clear( zed_canvas &canvas ) {
	float color[4] = { 0, 0, 0, 1 };
	app.graphics.device_context->ClearRenderTargetView( canvas.rtv, color );
	app.graphics.device_context->ClearDepthStencilView( canvas.dsv, D3D11_CLEAR_DEPTH, 0, 0 );
}

void zed_canvas_fill( zed_canvas &canvas, uint color_in ) {
	float color[4] = {
		( ( color_in >> 16 ) & 0xFF ) / 255.0f,
		( ( color_in >>  8 ) & 0xFF ) / 255.0f,
		( ( color_in       ) & 0xFF ) / 255.0f,
		1
	};

	app.graphics.device_context->ClearRenderTargetView( canvas.rtv, color );
	app.graphics.device_context->ClearDepthStencilView( canvas.dsv, D3D11_CLEAR_DEPTH, 0, 0 );
}

void zed_canvas_fill( zed_canvas &canvas, int r, int g, int b ) {
	float color[4] = { r/255.0f, g/255.0f, b/255.0f, 1 };
	app.graphics.device_context->ClearRenderTargetView( canvas.rtv, color );
	app.graphics.device_context->ClearDepthStencilView( canvas.dsv, D3D11_CLEAR_DEPTH, 0, 0 );
}

void zed_canvas_clear_stencil( zed_canvas &canvas ) {
	app.graphics.device_context->ClearDepthStencilView( canvas.dsv, D3D11_CLEAR_DEPTH, 0, 0 );
}
