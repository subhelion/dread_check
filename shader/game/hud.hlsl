#include "../game.hlsli"

struct vs_input {
	float3 position : POSITION;
	float3 normal   : NORMAL;
	float2 uv       : TEXCOORD;
};

struct ps_input {
	float4 position       : SV_POSITION;
	float4 position_world : POSITION0;
	float4 position_view  : POSITION1;
	float4 position_clip  : POSITION2;
	float3 normal_world   : NORMAL0;
	float3 normal_view    : NORMAL1;
	float2 uv             : TEXCOORD0;
};

ps_input vs( vs_input input ) {
	ps_input output;

	float4 position_model = float4( input.position, 1.0 );
	float4 position_world = mul( position_model,        matrix_world );
	float4 position_view  = mul( position_world, camera.matrix_view  );
	float4 position_clip  = mul( position_view,  camera.matrix_clip  );

	// output.position_model = position_model;
	output.position_world = position_world;
	output.position_view  = position_view;
	output.position_clip  = position_clip;
	output.position = output.position_clip; // note field with SV_POSITION semantic gets converted to ndc

	// output.position = mul( input.position, world_view_clip );

	//

	float3 normal_model = input.normal;
	float3 normal_world = mul( normal_model, (float3x3)matrix_world );
	// float3 normal_view  = mul( normal_model, (float3x3)camera.matrix_view );

	float3 normal_view  = mul( normal_model, (float3x3)camera.matrix_tiwv );

	// output.normal_model = normalize( input.normal );
	output.normal_world = normalize( normal_world );
	output.normal_view  = normalize( normal_view  );

	output.uv = input.uv;

	return output;
}

float4 ps( ps_input input ) : SV_TARGET {
	return float4( 1, 1, 1, 1 );
}
