#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/platform/d3d11.h>

#include "6_pass/0_input_layout.cpp"
#include "6_pass/1_rasterizer.cpp"
#include "6_pass/2_sampler.cpp"
#include "6_pass/3_blend.cpp"
#include "6_pass/4_shader.cpp"

// IA Input Assembler
// VS Vertex Shader
// GS Geometry Shader
// RS Rasterizer
// PS Pixel Shader
// OM Output Merger

enum zed_shader_type {
	shader_type_vs,
	shader_type_gs,
	shader_type_ps,
};

void compile_shader( string file, zed_shader_type type, zed_pass &pass, ID3DBlob **vsb, string ps_name = "ps" ) {
	int result;
	ID3DBlob *blob;

	if ( type == shader_type_vs ) result = compile_shader_from_file( file, "vs",    "vs_4_0", &blob );
	if ( type == shader_type_gs ) result = compile_shader_from_file( file, "gs",    "gs_4_0", &blob );
	if ( type == shader_type_ps ) result = compile_shader_from_file( file, ps_name, "ps_4_0", &blob );

	if ( result ) return;

	if ( type == shader_type_vs ) *vsb = blob;

	handle bp = blob->GetBufferPointer();
	size_t bs = blob->GetBufferSize();

	if ( type == shader_type_vs ) app.graphics.device->CreateVertexShader  ( bp, bs, 0, &pass.native.vs );
	if ( type == shader_type_gs ) app.graphics.device->CreateGeometryShader( bp, bs, 0, &pass.native.gs );
	if ( type == shader_type_ps ) app.graphics.device->CreatePixelShader   ( bp, bs, 0, &pass.native.ps );
}

void compile_shader( int id, zed_shader_type type, zed_pass &pass, ID3DBlob **vsb ) {
	int result;
	ID3DBlob *blob;

	if ( type == shader_type_vs ) result = compile_shader_from_resource( id, "vs", "vs_4_0", &blob );
	if ( type == shader_type_gs ) result = compile_shader_from_resource( id, "gs", "gs_4_0", &blob );
	if ( type == shader_type_ps ) result = compile_shader_from_resource( id, "ps", "ps_4_0", &blob );

	if ( result ) return;

	if ( type == shader_type_vs ) *vsb = blob;

	handle bp = blob->GetBufferPointer();
	size_t bs = blob->GetBufferSize();

	if ( type == shader_type_vs ) app.graphics.device->CreateVertexShader  ( bp, bs, 0, &pass.native.vs );
	if ( type == shader_type_gs ) app.graphics.device->CreateGeometryShader( bp, bs, 0, &pass.native.gs );
	if ( type == shader_type_ps ) app.graphics.device->CreatePixelShader   ( bp, bs, 0, &pass.native.ps );
}

//

void zed_pass_new( zed_pass &pass, string file ) {
	ID3DBlob *vsb;

	compile_shader( file, shader_type_vs, pass, &vsb );
	compile_shader( file, shader_type_gs, pass, 0    );
	compile_shader( file, shader_type_ps, pass, 0    );

	create_input_layout_from_shader( &pass.native, vsb );
}

void zed_pass_new( zed_pass &pass, string file, string ps_name ) {
	compile_shader( file, shader_type_ps, pass, 0, ps_name );
}

void zed_pass_new( zed_pass &pass, string file, D3D11_INPUT_ELEMENT_DESC *ied, uint ied_count ) {
	ID3DBlob *vsb;

	compile_shader( file, shader_type_vs, pass, &vsb );
	compile_shader( file, shader_type_gs, pass, 0    );
	compile_shader( file, shader_type_ps, pass, 0    );

	app.graphics.device->CreateInputLayout( ied, ied_count, vsb->GetBufferPointer(), vsb->GetBufferSize(), &pass.native.il );
}

//

void zed_pass_new( zed_pass &pass, int id ) {
	ID3DBlob *vsb = 0;

	compile_shader( id, shader_type_vs, pass, &vsb );
	compile_shader( id, shader_type_gs, pass, 0    );
	compile_shader( id, shader_type_ps, pass, 0    );

	create_input_layout_from_shader( &pass.native, vsb );
}

void zed_pass_new( zed_pass &pass, int id, D3D11_INPUT_ELEMENT_DESC *ied, uint ied_count ) {
	ID3DBlob *vsb;

	compile_shader( id, shader_type_vs, pass, &vsb );
	compile_shader( id, shader_type_gs, pass, 0    );
	compile_shader( id, shader_type_ps, pass, 0    );

	app.graphics.device->CreateInputLayout( ied, ied_count, vsb->GetBufferPointer(), vsb->GetBufferSize(), &pass.native.il );
}

//

void zed_pass_use( zed_texture &texture ) {
	if ( &texture == &texture_null ) {
		app.graphics.device_context->PSSetShaderResources( 0, 0, 0 );
	} else {
		app.graphics.device_context->PSSetShaderResources( 0, 1, &texture.view );
	}
}

ID3D11ShaderResourceView *null_srv[128];

void zed_pass_reset() {
	app.graphics.device_context->IASetInputLayout( 0 );
	app.graphics.device_context->VSSetShader( 0, 0, 0 );
	app.graphics.device_context->VSSetConstantBuffers( 0, 0, 0 );
	app.graphics.device_context->VSSetShaderResources( 0, 127, null_srv );
	app.graphics.device_context->GSSetShader( 0, 0, 0 );
	app.graphics.device_context->GSSetShaderResources( 0, 127, null_srv );
	app.graphics.device_context->RSSetState( 0 );
	app.graphics.device_context->PSSetShader( 0, 0, 0 );
	app.graphics.device_context->PSSetShaderResources( 0, 128, null_srv );
	app.graphics.device_context->OMSetBlendState( 0, 0, 0xffffffff );
	app.graphics.device_context->OMSetDepthStencilState( 0, 0 );
}

void zed_pass_set( zed_pass &pass ) {
	if ( &pass == &pass_null ) return;
	if ( pass.native.il ) app.graphics.device_context->IASetInputLayout( pass.native.il );
	if ( pass.native.vs ) app.graphics.device_context->VSSetShader( pass.native.vs, 0, 0 );
	if ( pass.native.gs ) app.graphics.device_context->GSSetShader( pass.native.gs, 0, 0 );
	if ( pass.native.rs ) app.graphics.device_context->RSSetState( pass.native.rs );
	if ( pass.native.ps ) app.graphics.device_context->PSSetShader( pass.native.ps, 0, 0 );
	                      app.graphics.device_context->PSSetSamplers( 0, 3, (ID3D11SamplerState *const *)&sampler_states );
	if ( pass.native.bs ) app.graphics.device_context->OMSetBlendState( pass.native.bs, 0, 0xffffffff );
	                      app.graphics.device_context->OMSetDepthStencilState ( app.graphics.dss, 1 );
	if ( pass.native.ds ) app.graphics.device_context->OMSetDepthStencilState ( pass.native.ds,   1 );
}

void zed_pass_reset( zed_pass &pass ) {
	zed_pass_reset();
	zed_pass_set( pass );
}
