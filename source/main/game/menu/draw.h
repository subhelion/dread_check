#pragma once

#include "../../../data/gfx.h"
#include "../../canvas.h"
#include "../../game.h"

#include <zed/app/graphics.h>

void game_menu_main( game_menu &menu, game_menu_signal signal );

void draw_title() {
	zed_pass_reset( pass_title );
	zed_pass_use( texture_title );

	float w = texture_title.size.x;
	float h = texture_title.size.y;

	game.draw.matrix_world = identity;

	float x = ( (float)canvas_x1.size.x - w ) / (float)canvas_x1.size.x;
	float y = ( (float)canvas_x1.size.y - h ) / (float)canvas_x1.size.y;
	float tw = (float)canvas_x1.size.x;
	float th = (float)canvas_x1.size.y;

	if ( split == game_split_duo ) {
		x = 0 + 1 / tw;
		tw = tw / 2 - 2 / tw;
		w = tw;
	}

	game.draw.matrix_world = game.draw.matrix_world * scale( w / tw, 1, 1 );
	game.draw.matrix_world = game.draw.matrix_world * scale( 2 );
	game.draw.matrix_world = game.draw.matrix_world * translate( -1 + x, -1 + y, 0 );

	game_draw_per_object_update();

	zed_mesh_draw( mesh_quad );
}

void draw_title_maze() {
	void zed_canvas_fill( zed_canvas &canvas, int r, int g, int b );
	zed_canvas_fill( canvas_x1, 0, 0, 170 );
	zed_pass_reset( pass_title );
	zed_pass_use( gfx_start_1984 );

	float w = texture_title.size.x;
	float h = texture_title.size.y;

	game.draw.matrix_world = identity;

	float x = ( (float)canvas_x1.size.x - w ) / (float)canvas_x1.size.x;
	float y = ( (float)canvas_x1.size.y - h ) / (float)canvas_x1.size.y;
	float tw = (float)canvas_x1.size.x;
	float th = (float)canvas_x1.size.y;

	if ( split == game_split_duo ) {
		x = 0 + 1 / tw;
		tw = tw / 2 - 2 / tw;
		w = tw;
	}

	game.draw.matrix_world = game.draw.matrix_world * scale( w / tw, 1, 1 );
	game.draw.matrix_world = game.draw.matrix_world * scale( 2 );
	game.draw.matrix_world = game.draw.matrix_world * translate( -1 + x, -1 + y, 0 );

	game_draw_per_object_update();

	zed_mesh_draw( mesh_quad );
}

void zed_draw_image( zed_texture texture, float x, float y ) {
	zed_pass_use( texture );

	float tw = (float)canvas_x1.size.x;
	float th = (float)canvas_x1.size.y;
	float w = texture.size.x;
	float h = texture.size.y;

	game.draw.matrix_world = identity;
	game.draw.matrix_world = game.draw.matrix_world * scale( w / tw, h / th, 1 );
	game.draw.matrix_world = game.draw.matrix_world * scale( 2 );
	game.draw.matrix_world = game.draw.matrix_world * translate( -1 + 2 * x / tw, 1 - 2 * y / th - 2 * h / th, 1 );

	game_draw_per_object_update();

	zed_mesh_draw( mesh_quad );
}

void zed_draw_rect( float x, float y, float w, float h, uint color = 0 ) {
	zed_pass_reset( pass_fill );

	float tw = (float)canvas_x1.size.x;
	float th = (float)canvas_x1.size.y;

	game.draw.matrix_world = identity;
	game.draw.matrix_world = game.draw.matrix_world * scale( w / tw, h / th, 1 );
	game.draw.matrix_world = game.draw.matrix_world * scale( 2 );
	game.draw.matrix_world = game.draw.matrix_world * translate( -1 + 2 * x / tw, 1 - 2 * y / th - 2 * h / th, 1 );

	game_draw_per_object_update();

	zed_mesh_draw( mesh_quad );
}

void zed_draw_rect_empty( float x, float y, float w, float h, uint color = 0, float b = 1 ) {
	zed_draw_rect( x,         y,         w, b, color );
	zed_draw_rect( x,         y,         b, h, color );
	zed_draw_rect( x,         y + h - b, w, b, color );
	zed_draw_rect( x + w - b, y,         b, h, color );
}

// todo unused
struct zed_sprite {
	zed_texture texture;
	float2      size;
};

// todo doesn't work
void zed_draw_image_cell( zed_texture texture, float x, float y, float w, float h, int i ) {
	zed_pass_reset( pass_face );
	zed_pass_use( texture );

	float tw = (float)canvas_x1.size.x;
	float th = (float)canvas_x1.size.y;

	game.draw.matrix_world = identity;
	game.draw.matrix_world = game.draw.matrix_world * scale( w / tw, h / th, 1 );
	game.draw.matrix_world = game.draw.matrix_world * scale( 2 );
	game.draw.matrix_world = game.draw.matrix_world * translate( -1 + 2 * x / tw, 1 - 2 * y / th - 2 * h / th, 1 );

	game_draw_per_object_update();

	game_draw_per_object_update();

	struct cell_t {
		uint tile;
	} cell[] = { (uint)i };

	zed_buffer_update( data_enemy, zed_data( cell ) );

	zed_mesh_draw( mesh_quad );
}

void game_menu_draw( game_menu &menu ) {
	zed_clear_stencil();

	switch ( menu.state.page ) {
		case game_menu_page_start:
		case game_menu_page_play:
		case game_menu_page_options:
		case game_menu_page_options_input:
		case game_menu_page_options_input_singleplayer:
		case game_menu_page_options_input_multiplayer:
		case game_menu_page_options_video:
		case game_menu_page_options_audio:
		case game_menu_page_options_data:
		case game_menu_page_pause:
			draw_title();
			break;
		case game_menu_page_maze:
			draw_title_maze();
			break;
	}

	//

	app_graphics_text_begin();
	game_menu_main( menu, game_menu_signal_render );
	app_graphics_text_finish();
}
