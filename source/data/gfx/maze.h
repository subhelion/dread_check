#pragma once

#include "../../main/maze.h"
#include "game.h"

#include <zed/app/graphics.h>
#include <zed/platform/d3d11.h>

zed_pass   pass_main_maze;
zed_pass   pass_maze;
zed_buffer data_maze;
zed_pass   pass_enemy_maze;
zed_pass   pass_sky_maze;
zed_pass   pass_chest;
zed_buffer data_chest;
zed_pass   pass_snow;
zed_buffer data_snow;

zed_texture gfx_maze;
zed_texture gfx_maze_mm;
zed_texture gfx_maze_mm_nn;
zed_texture gfx_maze_lod_a;
zed_texture gfx_maze_lod_b;
zed_texture gfx_maze_mm_x2;
zed_texture gfx_maze_mm_x4;
zed_texture gfx_maze_mm_x8;
zed_texture gfx_maze_mm_xx;

D3D11_INPUT_ELEMENT_DESC ied_maze[] = {
	{ "POSITION",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "NORMAL",     0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "TEXCOORD",   0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "I_POSITION", 0, DXGI_FORMAT_R32G32_FLOAT,    1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "I_SIZE",     0, DXGI_FORMAT_R32G32_FLOAT,    1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
};

D3D11_INPUT_ELEMENT_DESC ied_snow[] = {
	{ "I_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
};

void data_gfx_maze_init() {
	zed_pass_new( pass_main_maze,  "data/shader/maze/main.hlsl" );
	zed_pass_new( pass_sky_maze,   "data/shader/maze/sky.hlsl"  );
	zed_pass_new( pass_enemy_maze, "data/shader/maze/nazi.hlsl",  ied_enemy, 6 );
	zed_pass_new( pass_maze,       "data/shader/maze/maze.hlsl",  array_and_count( ied_maze ) );
	zed_pass_new( pass_chest,      "data/shader/maze/chest.hlsl", ied_maze, 4 );
	zed_pass_new( pass_snow,       "data/shader/maze/snow.hlsl",  ied_snow, 1 );

	zed_texture_new_2d( gfx_maze,       "data/texture/maze.dds"       );
	zed_texture_new_2d( gfx_maze_mm,    "data/texture/maze_mm.dds"    );
	zed_texture_new_2d( gfx_maze_mm_nn, "data/texture/maze_mm_nn.dds" );
	zed_texture_new_2d( gfx_maze_lod_a, "data/texture/maze_lod_a.dds" );
	zed_texture_new_2d( gfx_maze_lod_b, "data/texture/maze_lod_b.dds" );
	zed_texture_new_2d( gfx_maze_mm_x2, "data/texture/maze_mm_x2.dds" );
	zed_texture_new_2d( gfx_maze_mm_x4, "data/texture/maze_mm_x4.dds" );
	zed_texture_new_2d( gfx_maze_mm_x8, "data/texture/maze_mm_x8.dds" );
	zed_texture_new_2d( gfx_maze_mm_xx, "data/texture/maze_mm_xx.dds" );

	zed_buffer_new_instance( data_maze,  zed_data( maze.data  ) );
	zed_buffer_new_instance( data_chest, zed_data( maze.chest ) );
	zed_buffer_new_instance( data_snow,  zed_data( maze.snow  ) );
}
