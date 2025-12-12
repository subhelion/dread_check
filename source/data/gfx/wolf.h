#pragma once

#include "../../main/wolf.h"

#include <zed.h>
#include <zed/app/graphics.h>
#include <zed/platform/d3d11.h>

zed_pass pass_wolf_wall;
zed_pass pass_wolf_wall_n;
zed_pass pass_wolf_wall_d;
zed_pass pass_wolf_door_0;
zed_pass pass_wolf_door_1;
zed_pass pass_wolf_door_2;

zed_pass pass_wolf_sprite;
zed_pass pass_wolf_sprite_n;
zed_pass pass_wolf_sprite_d;

zed_pass pass_wolf_floor;
zed_pass pass_wolf_floor_n;
zed_pass pass_wolf_floor_d;

zed_pass pass_wolf_enemy;
zed_pass pass_wolf_debug;
zed_pass pass_wolf_map;
zed_pass pass_wolf_stencil;

zed_mesh mesh_wolf_wall;
zed_mesh mesh_wolf_door;

zed_buffer data_wolf_grid;
zed_buffer data_wolf_sprite;
zed_buffer data_wolf_enemy;

zed_texture texture_wolf;
zed_texture texture_wolf_sprite;
zed_texture texture_wolf_guard;

D3D11_INPUT_ELEMENT_DESC ied_wolf[] = {
	{ "POSITION",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "NORMAL",     0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "TEXCOORD",   0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "I_TILE",     0, DXGI_FORMAT_R32_UINT,        1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "I_TWEEN",    0, DXGI_FORMAT_R32_FLOAT,       1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
};

D3D11_INPUT_ELEMENT_DESC ied_wolf_sprites[] = {
	{ "POSITION",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "NORMAL",     0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "TEXCOORD",   0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "I_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "I_TILE",     0, DXGI_FORMAT_R32_UINT,        1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
};

D3D11_INPUT_ELEMENT_DESC ied_wolf_enemy[] = {
	{ "POSITION",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "NORMAL",     0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "TEXCOORD",   0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "I_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "I_TILE",     0, DXGI_FORMAT_R32_UINT,        1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "I_FACE",     0, DXGI_FORMAT_R32_UINT,        1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "I_FRAME",    0, DXGI_FORMAT_R32_UINT,        1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
};

void data_gfx_wolf_init() {
	zed_pass_new( pass_wolf_wall,   "data/shader/wolf/wall.hlsl", ied_wolf, 4 );
	zed_pass_new( pass_wolf_wall_n, "data/shader/wolf/wall.hlsl", "ps_normal" );
	zed_pass_new( pass_wolf_wall_d, "data/shader/wolf/wall.hlsl", "ps_depth" );
	zed_pass_new( pass_wolf_door_0, "data/shader/wolf/door_0.hlsl", ied_wolf, 5 );
	zed_pass_new( pass_wolf_door_1, "data/shader/wolf/door_1.hlsl", ied_wolf, 5 );
	zed_pass_new( pass_wolf_door_2, "data/shader/wolf/2.hlsl", ied_wolf, 5 );
	pass_wolf_door_0.rs = rasterizer_states.cull_front_biased;
	pass_wolf_door_1.rs = rasterizer_states.cull_none;

	zed_pass_new( pass_wolf_sprite,   "data/shader/wolf/sprite.hlsl", ied_wolf_sprites, 5 );
	zed_pass_new( pass_wolf_sprite_n, "data/shader/wolf/sprite-n.hlsl", "ps_normal" );
	zed_pass_new( pass_wolf_sprite_d, "data/shader/wolf/sprite-d.hlsl", "ps_depth" );

	zed_pass_new( pass_wolf_floor,   "data/shader/wolf/floor.hlsl" );
	zed_pass_new( pass_wolf_floor_n, "data/shader/wolf/floor.hlsl", "ps_normal" );
	zed_pass_new( pass_wolf_floor_d, "data/shader/wolf/floor.hlsl", "ps_depth"  );

	zed_pass_new( pass_wolf_enemy, "data/shader/wolf/enemy.hlsl", array_and_count( ied_wolf_enemy ) );
	zed_pass_new( pass_wolf_debug, "data/shader/wolf/debug.hlsl", array_and_count( ied_wolf_enemy ) );

	zed_pass_new( pass_wolf_map,     "data/shader/wolf/map.hlsl"     );
	zed_pass_new( pass_wolf_stencil, "data/shader/wolf/stencil.hlsl" );

	zed_mesh_new( mesh_wolf_wall, "data/model/wall.obj" );
	zed_mesh_new( mesh_wolf_door, "data/model/door.obj" );

	zed_buffer_new_instance( data_wolf_grid,   zed_data( wolf.grid   ) );
	zed_buffer_new_instance( data_wolf_sprite, zed_data( wolf.sprite ) );
	zed_buffer_new_instance( data_wolf_enemy,  zed_data( wolf.enemy  ) );

	zed_texture_new_2d( texture_wolf,        "data/wolf/wall.dds"  );
	zed_texture_new_2d( texture_wolf_sprite, "data/wolf/item.dds"  );
	zed_texture_new_2d( texture_wolf_guard,  "data/wolf/guard.dds" );
}
