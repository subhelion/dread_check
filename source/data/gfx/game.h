#pragma once

#include "../../main/game.h"

#include <zed/app/graphics.h>
#include <zed/platform/d3d11.h>

// common

zed_mesh   mesh_quad;
zed_mesh   mesh_cube;
zed_buffer buffer_quad_custom;
zed_pass   pass_fill;

// debug

zed_pass pass_ante;
zed_pass pass_debug_normal;
zed_pass pass_debug_depth;
zed_pass pass_debug_overdraw;

// title

// #define field( name ) zed_texture texture_title_##name;
// #include "../../data/chapter.inl"
// #undef field

zed_texture texture_title_main_0;
zed_texture texture_title_main_1;
zed_texture texture_title_main_2;
zed_texture texture_title_main_play;
zed_texture texture_title_main_action;
zed_texture texture_title_main_adventure;
zed_texture texture_title_main_options;

zed_texture texture_title_alien_intel_0;
zed_texture texture_title_alien_intel_1;
zed_texture texture_title_alien_intel_classic;
zed_texture texture_title_blue_monsoon_0;
zed_texture texture_title_blue_monsoon_1;
zed_texture texture_title_blue_monsoon_2;
zed_texture texture_title_swat_city_0;
zed_texture texture_title_swat_city_1;

zed_texture texture_title_blood_flush;
zed_texture texture_title_cryoshock;
zed_texture texture_title_draugb;
zed_texture texture_title_full_metal_express;
zed_texture texture_title_gate_quake;
zed_texture texture_title_hazard_company;
zed_texture texture_title_horse_war;
zed_texture texture_title_howling_commandos;
zed_texture texture_title_plastic_platoon;
zed_texture texture_title_primitive_streak;
zed_texture texture_title_route_66;
zed_texture texture_title_swat_city;
zed_texture texture_title_threefold_path;

zed_pass pass_title;

// menu

zed_texture texture_faces;
zed_texture texture_face_default;
zed_pass    pass_face;
zed_texture gfx_face[150];

D3D11_INPUT_ELEMENT_DESC ied_face[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "I_TILE",   0, DXGI_FORMAT_R32_UINT,        1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
};

// sky

zed_texture texture_sky;
zed_pass    pass_sky;
zed_pass    pass_sky_n;
zed_pass    pass_sky_d;

// main

zed_pass pass_main;
zed_pass pass_depth;

// player

zed_mesh mesh_player;
zed_mesh mesh_revolver;
zed_mesh mesh_shotgun;
zed_mesh mesh_shotgun_open;
zed_mesh mesh_ak47;
zed_mesh mesh_hand;
zed_mesh mesh_hand_right;
zed_mesh mesh_knife;
zed_mesh mesh_ciws;
zed_mesh mesh_light;
zed_mesh mesh_chute;
zed_mesh mesh_bag;

// enemy

zed_pass   pass_enemy;
zed_mesh   mesh_enemy;
zed_buffer data_enemy;
zed_pass   pass_enemy_hitbox;

D3D11_INPUT_ELEMENT_DESC ied_enemy[] = {
	{ "POSITION",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "NORMAL",     0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "TEXCOORD",   0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "I_POSITION", 0, DXGI_FORMAT_R32G32_FLOAT,    1,                            0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "I_ROTATION", 0, DXGI_FORMAT_R32_FLOAT,       1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "I_COLOR",    0, DXGI_FORMAT_R32G32B32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
};

// bullet

zed_pass   pass_bullet;
zed_mesh   mesh_bullet;
zed_buffer data_bullet;

D3D11_INPUT_ELEMENT_DESC ied_bullet[] = {
	{ "POSITION",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "NORMAL",     0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "TEXCOORD",   0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "I_MATRIX",   0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,                            0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "I_MATRIX",   1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,                           16, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "I_MATRIX",   2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,                           32, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "I_MATRIX",   3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,                           48, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "I_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "I_ROTATION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "I_COLOR",    0, DXGI_FORMAT_R32G32B32_FLOAT,    1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
};

// ground

zed_mesh mesh_ground;

// world

zed_pass   pass_world;
zed_buffer data_world;

D3D11_INPUT_ELEMENT_DESC ied_world[] = {
	{ "POSITION",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "NORMAL",     0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "TEXCOORD",   0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
	{ "I_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1,                            0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
};

// pc

zed_pass    pass_pc;
zed_pass    pass_pc_screen;
zed_mesh    mesh_pc;
zed_mesh    mesh_pc_screen;
zed_texture texture_pc_screen;
zed_canvas  canvas_pc_screen;

zed_texture gfx_start_1984;
zed_texture gfx_start_1992;

// hud

zed_pass pass_hud;

void data_gfx_game_init() {
	// common

	zed_mesh_new( mesh_quad, "data/model/quad.obj"   );
	zed_mesh_new( mesh_cube, "data/model/cube-1.obj" );

	zed_pass_new( pass_fill, "data/shader/game/fill.hlsl" );

	// debug

	zed_pass_new( pass_debug_normal,   "data/shader/wolf/wall-n.hlsl",    "ps" );
	zed_pass_new( pass_debug_depth,    "data/shader/wolf/wall-d.hlsl",    "ps" );
	zed_pass_new( pass_debug_overdraw, "data/shader/debug/overdraw.hlsl", "ps" );
	pass_debug_overdraw.bs = blend_states.alpha;

	// title

	// #define field( name ) zed_texture_new_2d( texture_title_##name, "data/texture/title/" #name ".dds" );
	// #include "../../data/chapter.inl"
	// #undef field

	zed_texture_new_2d( texture_title_main_0,              "data/texture/title/dread_check_0.dds"         );
	zed_texture_new_2d( texture_title_main_1,              "data/texture/title/dread_check_1.dds"         );
	zed_texture_new_2d( texture_title_main_2,              "data/texture/title/dread_check_2.dds"         );
	zed_texture_new_2d( texture_title_main_play,           "data/texture/title/dread_check_play.dds"      );
	zed_texture_new_2d( texture_title_main_action,         "data/texture/title/dread_check_action.dds"    );
	zed_texture_new_2d( texture_title_main_adventure,      "data/texture/title/dread_check_adventure.dds" );
	zed_texture_new_2d( texture_title_main_options,        "data/texture/title/dread_check_options.dds"   );

	zed_texture_new_2d( texture_title_alien_intel_0,       "data/texture/title/alien_intel_0.dds"         );
	zed_texture_new_2d( texture_title_alien_intel_1,       "data/texture/title/alien_intel_1.dds"         );
	zed_texture_new_2d( texture_title_alien_intel_classic, "data/texture/title/alien_intel_classic.dds"   );
	zed_texture_new_2d( texture_title_swat_city_0,         "data/texture/title/swat_city_0.dds"           );
	zed_texture_new_2d( texture_title_swat_city_1,         "data/texture/title/swat_city_1.dds"           );
	zed_texture_new_2d( texture_title_blue_monsoon_0,      "data/texture/title/blue_monsoon_0.dds"        );
	zed_texture_new_2d( texture_title_blue_monsoon_1,      "data/texture/title/blue_monsoon_1.dds"        );
	zed_texture_new_2d( texture_title_blue_monsoon_2,      "data/texture/title/blue_monsoon_2.dds"        );

	zed_texture_new_2d( texture_title_blood_flush,         "data/texture/title/blood_flush.dds"           );
	zed_texture_new_2d( texture_title_cryoshock,           "data/texture/title/cryoshock.dds"             );
	zed_texture_new_2d( texture_title_draugb,              "data/texture/title/draugb.dds"                );
	zed_texture_new_2d( texture_title_full_metal_express,  "data/texture/title/full_metal_express.dds"    );
	zed_texture_new_2d( texture_title_gate_quake,          "data/texture/title/gate_quake.dds"            );
	zed_texture_new_2d( texture_title_hazard_company,      "data/texture/title/hazard_company.dds"        );
	zed_texture_new_2d( texture_title_horse_war,           "data/texture/title/horse_war.dds"             );
	zed_texture_new_2d( texture_title_howling_commandos,   "data/texture/title/howling_commandos.dds"     );
	zed_texture_new_2d( texture_title_plastic_platoon,     "data/texture/title/plastic_platoon.dds"       );
	zed_texture_new_2d( texture_title_primitive_streak,    "data/texture/title/primitive_streak.dds"      );
	zed_texture_new_2d( texture_title_route_66,            "data/texture/title/route_66.dds"              );
	zed_texture_new_2d( texture_title_swat_city,           "data/texture/title/swat_city.dds"             );
	zed_texture_new_2d( texture_title_threefold_path,      "data/texture/title/threefold_path.dds"        );

	zed_pass_new( pass_title, "data/shader/game/title.hlsl" );

	// menu

	zed_texture_new_2d( texture_faces, "data/texture/faces.dds" );
	zed_texture_new_2d( texture_face_default, "data/texture/default.dds" );
	zed_pass_new( pass_face, "data/shader/game/face.hlsl", ied_face, 4 );

	for ( int i = 0; i < 150; i ++ ) {
		char temp[32];
		sprintf( temp, "data/texture/face/%i.dds", i );
		zed_texture_new_2d( gfx_face[i], temp );
	}

	// sky

	zed_texture_load_cube( texture_sky, "data/texture/sky.dds" );
	zed_pass_new( pass_sky,   "data/shader/game/sky.hlsl"              );
	zed_pass_new( pass_sky_n, "data/shader/game/sky.hlsl", "ps_normal" );
	zed_pass_new( pass_sky_d, "data/shader/game/sky.hlsl", "ps_depth"  );

	// main

	zed_pass_new( pass_main,  "data/shader/game/main.hlsl"  );
	zed_pass_new( pass_depth, "data/shader/game/depth.hlsl" );

	// player

	zed_mesh_new( mesh_player,       "data/model/player.obj",    0.92 );
	zed_mesh_new( mesh_revolver,     "data/model/revolver.obj" );
	zed_mesh_new( mesh_shotgun,      "data/model/shotgun.obj" );
	zed_mesh_new( mesh_shotgun_open, "data/model/shotgun_open.obj" );
	zed_mesh_new( mesh_ak47,         "data/model/ak47.obj",      0.01 * 0.9 );
	zed_mesh_new( mesh_hand,         "data/model/hand.obj",      0.04 );
	zed_mesh_new( mesh_hand_right,   "data/model/hand_left.obj", 0.04 );
	zed_mesh_new( mesh_knife,        "data/model/knife.obj",     0.04 );
	// zed_mesh_new( mesh_ciws,         "data/model/ciws.obj" );
	zed_mesh_new( mesh_light,        "data/model/light.obj",     1.0 );
	zed_mesh_new( mesh_chute,        "data/model/chute.obj",     1.0 );
	zed_mesh_new( mesh_bag,          "data/model/bag.obj",       1.0 );

	// enemy

	zed_pass_new( pass_enemy, "data/shader/game/enemy.hlsl", ied_enemy, 6 );
	zed_mesh_new( mesh_enemy, "data/model/enemy.obj", 0.95 );
	zed_buffer_new_instance( data_enemy, zed_data( game.data.enemy ) );
	zed_pass_new( pass_enemy_hitbox, "data/shader/game/enemy_hitbox.hlsl", ied_enemy, 6 );
	pass_enemy_hitbox.rs = rasterizer_states.wireframe;

	// bullet

	zed_pass_new( pass_bullet, "data/shader/game/bullet.hlsl", ied_bullet, 10 );
	zed_mesh_new( mesh_bullet, "data/model/cube-0.obj" );
	zed_buffer_new_instance( data_bullet, zed_data( game.data.bullet ) );

	// ground

	zed_mesh_new_plane( mesh_ground, 2, 2, 1024 * 32 );

	// world

	zed_pass_new( pass_world, "data/shader/game/world.hlsl", ied_world, 4 );
	zed_buffer_new_instance( data_world, zed_data( game_data_world ) );

	// pc

	zed_pass_new( pass_pc,        "data/shader/wolf/pc.hlsl"     );
	zed_pass_new( pass_pc_screen, "data/shader/wolf/screen.hlsl" );
	zed_mesh_new( mesh_pc,        "data/model/pc-body.obj"       );
	zed_mesh_new( mesh_pc_screen, "data/model/pc-screen.obj"     );
	zed_texture_new_2d( texture_pc_screen, "data/texture/start/start.dds" );
	zed_texture_new_2d( gfx_start_1992,    "data/texture/start/1992.dds"  );
	zed_texture_new_2d( gfx_start_1984,    "data/texture/start/1984.dds"  );

	zed_canvas_new( canvas_pc_screen, 320, 240 );

	// hud

	zed_pass_new( pass_hud, "data/shader/game/hud.hlsl"   );
}
