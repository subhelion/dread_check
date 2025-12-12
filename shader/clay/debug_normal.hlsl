#include "../game.hlsli"

struct vs_input {
	float3 position : POSITION;
	float3 normal   : NORMAL;
	float2 uv       : TEXCOORD;
};

struct ps_input {
	float4 position : SV_POSITION;

	float4 position_world : POSITION0;
	float4 position_view  : POSITION1;
	float4 position_clip  : POSITION2;

	float3 normal_world : NORMAL0;
	float3 normal_view  : NORMAL1;
	// float3 normal_face : NORMAL2;

	float2 uv : TEXCOORD0;
};

ps_input vs( vs_input input ) {
	ps_input output;

	float4 position_model = float4( input.position.xyz, 1.0 );
	float4 position_world = mul( position_model,        matrix_world );
	float4 position_view  = mul( position_world, camera.matrix_view  );
	float4 position_clip  = mul( position_view,  camera.matrix_clip  );

	output.position_world = position_world;
	output.position_view  = position_view;
	output.position_clip  = position_clip;
	output.position = output.position_clip;

	//

	float3 normal_model = input.normal;
	float3 normal_world = mul( normal_model, (float3x3)matrix_world       );
	float3 normal_view  = mul( normal_model, (float3x3)camera.matrix_tiwv );

	output.normal_world = normalize( normal_world );
	output.normal_view  = normalize( normal_view  );

	output.uv = input.uv;

	return output;
}

float4 ps( ps_input input ) : SV_TARGET {
	input.normal_world = normalize( input.normal_world );
	input.normal_view  = normalize( input.normal_view  );

	float3 normal      = input.normal_world;
	float3 normal_view = input.normal_view;

	//

	float3 color;

	//

	float3 normal_debug = normal_view;

    normal_debug.x = normal_debug.x *  0.5 + 0.5;
    normal_debug.y = normal_debug.y *  0.5 + 0.5;
    normal_debug.z = normal_debug.z * -0.5 + 0.5;

	//

	color = normal_debug;

	return float4( color, 1.0 );
}
