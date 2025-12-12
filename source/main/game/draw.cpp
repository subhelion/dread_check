#include "draw/split.h"
#include "draw.h"

#include "../../data/gfx.h"

#include "draw/update.cpp"

#include "draw/main.cpp"
#include "draw/hud.cpp"
#include "draw/vignette.cpp"

void game_menu_draw( game_menu &menu );

void game_draw_init() {
	zed_buffer_new_uniform( data_per_scene,  sizeof( game_draw_per_scene  ) );
	zed_buffer_new_uniform( data_per_frame,  sizeof( game_draw_per_frame  ) );
	zed_buffer_new_uniform( data_per_object, sizeof( game_draw_per_object ) );
	zed_buffer_new_uniform( data_alpha,      sizeof( game_draw_alpha      ) );

	uint slot = 0;

	zed_buffer_use_uniform( data_per_scene,  slot++ );
	zed_buffer_use_uniform( data_per_frame,  slot++ );
	zed_buffer_use_uniform( data_per_object, slot++ );
	// note slot 3 is buffer_studio
	zed_buffer_use_uniform( data_alpha, 4 );

	game_draw_vignette_init();
}

//

// sky

void draw_sky() {
	zed_camera temp = game.camera;
	temp.position   = { 0, 0, 0 };
	zed_camera_update( temp, &game.draw.camera );
	game_draw_per_frame_update();
	zed_mesh_draw_primitive( zed_primitive_triangle_list, 3 );
}

void scene_game_draw() {
	// main
	game_draw_main();

	// sky

	zed_pass_reset();
	zed_pass_set( pass_sky );
	zed_pass_set( pass_ante );
	if ( view_mode == 1 ) zed_pass_set( pass_sky_n );
	if ( view_mode == 2 ) zed_pass_set( pass_sky_d );
	zed_pass_use( texture_sky );
	game_draw_set_camera_i draw_sky();

	zed_camera_update( game.camera, &game.draw.camera );
	game_draw_per_frame_update();

	zed_pass_use();

	// bullet

	zed_pass_reset( pass_bullet );
	game.draw.per_object.matrix_world = identity;
	game_draw_per_object_update();
	zed_buffer_update( data_bullet, zed_data( game.data.bullet ) );
	game_draw_set_camera_i game_draw_bullet();
}

void scene_maze_draw() {
	if ( not game.is_started ) return;
	void maze_draw();
	maze_draw();
}

void scene_wolf_draw() {
	void maze_draw();
	maze_draw();
	void wolf_draw();
	wolf_draw();
}

void game_draw() {
	switch ( game.scene ) {
		case scene_game: scene_game_draw(); break;
		case scene_maze: scene_maze_draw(); break;
		case scene_wolf: scene_wolf_draw(); break;
	}

	game_draw_set_camera_i game_menu_draw( game.menu[i] );
	game_draw_vignette();
	zed_clear_stencil();
	game_draw_hud();
}

void game_draw_ui() {
	// note
	return;

	// todo
	void game_canvas_set_split_view_native( int i );
	void game_canvas_draw_per_camera_native( void(*f)() );

	// enemy hitbox

	game.draw.per_object.matrix_world = identity * translate( -0.5, 0, -0.5 );// * scale( 0.6, 1.5, 0.4 );
	game_draw_per_object_update();
	zed_buffer_update( data_enemy, zed_data( game.data.enemy ) );
	zed_pass_reset( pass_enemy_hitbox );
	game_canvas_draw_per_camera_native( game_draw_enemy_hitbox );
}
