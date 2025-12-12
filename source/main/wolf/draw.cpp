#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/camera.h>
#include <zed/xmath.h>

#include <zed/platform/d3d11.h>

#include "../../data/gfx.h"

#include "../canvas.h"
#include "../game/draw.h"
#include "../game.h"
#include "../wolf.h"

wolf_enemy enemy_temp[1024];

int frame_time = 0;

void wolf_draw_wall  () { zed_mesh_draw_instanced( mesh_wolf_wall, &data_wolf_grid, 64 * 64 ); }
void wolf_draw_door_0() { zed_mesh_draw_instanced( mesh_wolf_door, &data_wolf_grid, 64 * 64 ); }
void wolf_draw_door_1() { zed_mesh_draw_instanced( mesh_quad,      &data_wolf_grid, 64 * 64 ); }
void wolf_draw_door_2() { zed_mesh_draw_instanced( mesh_cube,      &data_wolf_grid, 64 * 64 ); }

void wolf_draw_sprite() {
	game.draw.per_object.matrix_world = translate( -0.5, 0, 0 ) * rotate( dtor( game.camera.rotation.x ), dtor( game.camera.rotation.y ), 0 ) * translate( 0.5, 0, 0.5 );
	game.draw.per_object.matrix_world = translate( -0.5, 0, 0 ) * rotate( 0, dtor( game.camera.rotation.y ), 0 ) * translate( 0.5, 0, 0.5 );
	game_draw_per_object_update();
	zed_mesh_draw_instanced( mesh_quad, &data_wolf_sprite, wolf.sprite_i );
}

void wolf_draw_enemy() {
	// game.draw.per_object.matrix_world = translate( -0.5, 0, 0 ) * rotate( dtor( game.camera.rotation.x ), dtor( game.camera.rotation.y ), 0 );
	game.draw.per_object.matrix_world = translate( -0.5, 0, 0 ) * rotate( 0, dtor( game.camera.rotation.y ), 0 );
	game_draw_per_object_update();

	//

	float position_z = game.camera.position.z / wolf_scale;
	float position_x = game.camera.position.x / wolf_scale;

	for ( int i = 0; i < wolf.enemy_i; i++ ) {
		if ( enemy_temp[i].frame == frame_dead ) {
			enemy_temp[i].face = 4;
			continue;
		}

		if ( wolf.enemy[i].frame == 0 ) {
			float angle = atan2(
				enemy_temp[i].position.z - position_z,
				enemy_temp[i].position.x - position_x
			);

			enemy_temp[i].face  = int( enemy_temp[i].face - angle * 8 / 2 / 3.1456927 + 8.5 ) % 8;
			continue;
		}

		switch ( wolf.enemy[i].face ) {
			case wolf_8e : enemy_temp[i].position = wolf.enemy[i].position + float3( -1,  0,  0 ) * float( frame_time % 200 ) / 200; break;
			case wolf_8ne: enemy_temp[i].position = wolf.enemy[i].position + float3( -1,  0, -1 ) * float( frame_time % 200 ) / 200; break;
			case wolf_8n : enemy_temp[i].position = wolf.enemy[i].position + float3(  0,  0, -1 ) * float( frame_time % 200 ) / 200; break;
			case wolf_8nw: enemy_temp[i].position = wolf.enemy[i].position + float3(  1,  0, -1 ) * float( frame_time % 200 ) / 200; break;
			case wolf_8w : enemy_temp[i].position = wolf.enemy[i].position + float3(  1,  0,  0 ) * float( frame_time % 200 ) / 200; break;
			case wolf_8sw: enemy_temp[i].position = wolf.enemy[i].position + float3(  1,  0,  1 ) * float( frame_time % 200 ) / 200; break;
			case wolf_8s : enemy_temp[i].position = wolf.enemy[i].position + float3(  0,  0,  1 ) * float( frame_time % 200 ) / 200; break;
			case wolf_8se: enemy_temp[i].position = wolf.enemy[i].position + float3( -1,  0,  1 ) * float( frame_time % 200 ) / 200; break;
		}

		float angle = atan2(
			enemy_temp[i].position.z - position_z,
			enemy_temp[i].position.x - position_x
		);

		enemy_temp[i].face  = int( enemy_temp[i].face - angle * 8 / 2 / 3.1456927 + 8.5 ) % 8;

		if ( enemy_temp[i].frame ) enemy_temp[i].frame = 1 + ( enemy_temp[i].frame + frame_time / 15 ) % 4;
	}

	zed_buffer_update( data_wolf_enemy, zed_data( enemy_temp ) );
	zed_mesh_draw_instanced( mesh_quad, &data_wolf_enemy, wolf.enemy_i );
}

void wolf_draw_pc() {
	game.draw.per_object.matrix_world = scale(0.3) * translate( wolf_pc.position );
	game_draw_per_object_update();
	zed_mesh_draw( mesh_pc );
	game.draw.per_object.matrix_world = translate( -0.5, -1, -0.5 ) * scale( 1.6, 0.05, 1.6) * translate( wolf_pc.position );
	game_draw_per_object_update();
	zed_mesh_draw( mesh_cube );
	game.draw.per_object.matrix_world = translate( -0.5, -1, -0.5 ) * scale( 0.1, 1, 0.1 ) * translate( wolf_pc.position );
	game_draw_per_object_update();
	zed_mesh_draw( mesh_cube );
	game.draw.per_object.matrix_world = translate( -0.5, 0, -0.5 ) * scale( 0.5, 0.05, 0.5 ) * translate( 0, -0.4 * wolf_scale, 0 ) * translate( wolf_pc.position );
	game_draw_per_object_update();
	zed_mesh_draw( mesh_cube );
}

void pass_wolf_pc_screen_draw() { zed_mesh_draw( mesh_pc_screen ); }

void wolf_draw_floor() {
	zed_camera temp = game.camera;
	temp.position   = { 0, 0, 0 };
	zed_camera_update( temp, &game.draw.camera );
	game_draw_per_frame_update();

	zed_mesh_draw_primitive( zed_primitive_triangle_list, 3 );
}

void wolf_draw() {
	// game.camera = game.data.camera[0];
	// zed_camera_update( game.camera, &game.draw.camera );
	// game_draw_per_frame_update();

	game.draw.per_object.matrix_world = identity * scale( wolf_scale );
	game_draw_per_object_update();

	zed_buffer_update( data_wolf_grid, zed_data( wolf.grid ) );

	zed_pass pass_ante_wall   = pass_null;
	zed_pass pass_ante_sprite = pass_null;
	zed_pass pass_ante_floor  = pass_null;

	if ( view_mode == 1 ) {
		pass_ante_wall    = pass_wolf_wall_n;
		pass_ante_sprite  = pass_wolf_sprite_n;
		pass_ante_floor   = pass_wolf_floor_n;
	}

	if ( view_mode == 2 ) {
		pass_ante_wall    = pass_wolf_wall_d;
		pass_ante_sprite  = pass_wolf_sprite_d;
		pass_ante_floor   = pass_wolf_floor_n;
	}

	if ( view_mode == 3 ) {
		pass_ante_wall   = pass_debug_overdraw;
		pass_ante_sprite = pass_debug_overdraw;
		pass_ante_floor  = pass_debug_overdraw;
	}

	// todo
	bool set_camera( int i );

	//

	zed_pass_reset();
	zed_pass_set( pass_wolf_wall );
	zed_pass_set( pass_ante_wall );
	zed_pass_use( texture_wolf );
	game_draw_set_camera_i wolf_draw_wall();

	//

	zed_pass_reset();
	zed_pass_set( pass_wolf_door_0 );
	zed_pass_set( pass_ante_wall );
	zed_pass_use( texture_wolf );
	game_draw_set_camera_i wolf_draw_door_0();

	zed_pass_reset();
	zed_pass_set( pass_wolf_door_1 );
	zed_pass_set( pass_ante_wall );
	game_draw_set_camera_i wolf_draw_door_1();

	zed_pass_reset();
	zed_pass_set( pass_wolf_door_2 );
	zed_pass_set( pass_ante_wall );
	game_draw_set_camera_i wolf_draw_door_2();

	//

	zed_pass_reset();
	zed_pass_set( pass_wolf_sprite );
	zed_pass_set( pass_ante_sprite );
	zed_pass_use( texture_wolf_sprite );
	zed_buffer_update( data_wolf_sprite, zed_data( wolf.sprite ) );
	game_draw_set_camera_i wolf_draw_sprite();

	//

	zed_pass_reset();
	zed_pass_set( pass_wolf_enemy  );
	zed_pass_set( pass_ante_sprite );
	zed_pass_use( texture_wolf_guard );
	memcpy( enemy_temp, wolf.enemy, sizeof( wolf.enemy ) );
	game_draw_set_camera_i wolf_draw_enemy();

	//

// 	zed_pass_reset();
// 	zed_pass_set( pass_pc_screen );
// 	zed_pass_set( pass_ante_wall );
// 	game.draw.per_object.matrix_world = scale(0.3) * translate( wolf_pc.position );
// 	game_draw_per_object_update();
// 	zed_pass_use( texture_pc_screen );
// 	game_draw_set_camera_i pass_wolf_pc_screen_draw();
//
// 	zed_pass_reset();
// 	zed_pass_set( pass_pc );
// 	zed_pass_set( pass_ante_wall );
// 	game_draw_set_camera_i wolf_draw_pc();

	//

	zed_pass_reset();
	zed_pass_set( pass_wolf_floor );
	zed_pass_set( pass_ante_floor );
	game_draw_set_camera_i wolf_draw_floor();
}
