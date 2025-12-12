#include "../game.hlsli"

struct vs_input {
	float3 position : POSITION;
	float3 normal   : NORMAL;
	float2 uv       : TEXCOORD;
};

struct ps_input {
	float4 position : SV_Position;
	float2 uv       : TEXCOORD;
};

ps_input vs( vs_input input ) {
	ps_input output;

	float4 position_model = float4( input.position, 1.0 );
	float4 position_world = mul( position_model,        matrix_world );
	float4 position_view  = mul( position_world, camera.matrix_view  );
	float4 position_clip  = mul( position_view,  camera.matrix_clip  );

	output.position = position_clip;

	//

	output.uv = input.uv;

	return output;
}

float4 ps( ps_input input ) : SV_TARGET {
	return float4( 1, 1, 1, 1 );
}
