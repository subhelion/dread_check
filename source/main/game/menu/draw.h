#pragma once

#include "../../../data/chapter.h"
#include "../../../data/color.h"
#include "../../../data/gfx.h"
#include "../../canvas.h"
#include "../../game.h"

#include <zed/app/graphics.h>

void game_menu_main( game_menu &menu, game_menu_signal signal );
void zed_canvas_fill( zed_canvas &canvas, uint color_in );
void zed_canvas_fill( zed_canvas &canvas, int r, int g, int b );

float t_spin;

void draw_title_layer( bool spin = false ) {
	t_spin += 1;

	float w = 320; // texture_title.size.x;
	float h = 240; // texture_title.size.y;

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
	if ( spin ) game.draw.matrix_world = game.draw.matrix_world * rotate( 0, 0, sin( t_spin * 0.001 ) * 3.1415926 / 12  );
	if ( spin ) game.draw.matrix_world = game.draw.matrix_world * scale( 4 );

	game_draw_per_object_update();

	zed_mesh_draw( mesh_quad );
}

int   t_bmt_flash = 0;
int   i_bmt_flash = 0;
char *c_bmt_flash = "__x_x____x__x_x_xxx_x___x";

void draw_title() {
	switch ( chapter_current ) {
		case chapter_none:

		if ( game.menu[0].state.page >= game_menu_page_options and game.menu[0].state.page <= game_menu_page_credits ) {
			zed_canvas_fill( canvas_x1, 0xBB007E );
		} else {
			zed_canvas_fill( canvas_x1, 0xF7E557 );
		}

		break;

		case chapter_alien_intel_classic:
		case chapter_alien_intel:
		zed_canvas_fill( canvas_x1, 0xBD0029 );
		break;

		case chapter_blue_monsoon:
		zed_canvas_fill( canvas_x1, 0x000000 );
		break;

		case chapter_blood_flush:              zed_canvas_fill( canvas_x1, 0x000000 ); break;
		case chapter_blood_flush_vintage:      zed_canvas_fill( canvas_x1, 0x000000 ); break;
		case chapter_cryoshock:                zed_canvas_fill( canvas_x1, 0xECFFFA ); break;
		case chapter_draugb:                   zed_canvas_fill( canvas_x1, 0x000000 ); break;
		case chapter_full_metal_express:       zed_canvas_fill( canvas_x1, 0x000000 ); break;
		case chapter_gate_quake_classic:       zed_canvas_fill( canvas_x1, 0x000000 ); break;
		case chapter_gate_quake:               zed_canvas_fill( canvas_x1, 0x000000 ); break;
		case chapter_gate_quake_4000:          zed_canvas_fill( canvas_x1, 0x000000 ); break;
		case chapter_hazard_company:           zed_canvas_fill( canvas_x1, 0x000000 ); break;
		case chapter_horse_war:                zed_canvas_fill( canvas_x1, 0x000000 ); break;
		case chapter_horse_war_3000:           zed_canvas_fill( canvas_x1, 0x000000 ); break;
		case chapter_howling_commandos:        zed_canvas_fill( canvas_x1, 0x000000 ); break;
		case chapter_plastic_platoon:          zed_canvas_fill( canvas_x1, 0x000000 ); break;
		case chapter_primitive_streak:         zed_canvas_fill( canvas_x1, 0x000000 ); break;
		case chapter_red_cry:                  zed_canvas_fill( canvas_x1, 0x000000 ); break;
		case chapter_route_66:                 zed_canvas_fill( canvas_x1, 0x000000 ); break;
		case chapter_swat_city:                zed_canvas_fill( canvas_x1, 0x000000 ); break;
		case chapter_swat_city_300:            zed_canvas_fill( canvas_x1, 0x000000 ); break;
		case chapter_threefold_path:           zed_canvas_fill( canvas_x1, 0x000000 ); break;
		case chapter_wuerm_arctigeddon:        zed_canvas_fill( canvas_x1, 0x000000 ); break;
		case chapter_wuerm_arctigeddon_modern: zed_canvas_fill( canvas_x1, 0x000000 ); break;
	}

	zed_pass_reset( pass_title );

	if ( chapter_current == chapter_none ) {
		game_menu_page page = game.menu[0].state.page;

		if ( page == game_menu_page_start ) {
			zed_pass_use( texture_title_main_0 );
			draw_title_layer( true );
			zed_pass_use( texture_title_main_1 );
			draw_title_layer();
			zed_pass_use( texture_title_main_2 );
			draw_title_layer();
		} else {
			if ( page >= game_menu_page_play and page < game_menu_page_play_max ) {
				zed_pass_use( texture_title_main_play );
				draw_title_layer();
			}

			if ( page >= game_menu_page_play_action and page < game_menu_page_play_action_max) {
				zed_pass_use( texture_title_main_action );
				draw_title_layer();
			}

			if ( page >= game_menu_page_play_adventure and page < game_menu_page_play_adventure_max and chapter_current == chapter_none ) {
				zed_pass_use( texture_title_main_adventure );
				draw_title_layer();
			}

			if ( page >= game_menu_page_options and page < game_menu_page_options_max ) {
				zed_pass_use( texture_title_main_options );
				draw_title_layer();
			}
		}
	}

	switch ( chapter_current ) {
		case chapter_alien_intel_classic:
		zed_pass_use( texture_title_alien_intel_classic );
		draw_title_layer();
		case chapter_alien_intel:
		zed_pass_use( texture_title_alien_intel_0 );
		draw_title_layer();
		zed_pass_use( texture_title_alien_intel_1 );
		draw_title_layer();
		break;

		case chapter_blue_monsoon:
		zed_pass_use( texture_title_blue_monsoon_0 );
		draw_title_layer();

		t_bmt_flash += 1;

		if ( t_bmt_flash >= 50 ) {
			t_bmt_flash = 0;
			i_bmt_flash = ( i_bmt_flash + 1 ) % 24;
		}

		if ( c_bmt_flash[i_bmt_flash] == 'x' ) {
			zed_pass_use( texture_title_blue_monsoon_2 );
		} else {
			zed_pass_use( texture_title_blue_monsoon_1 );
		}

		draw_title_layer();
		break;

		case chapter_draugb:
		zed_pass_use( texture_title_draugb );
		draw_title_layer();
		break;

		case chapter_swat_city:
		t_bmt_flash += 1;

		if ( t_bmt_flash >= 100 ) {
			t_bmt_flash = 0;
			i_bmt_flash = ( i_bmt_flash + 1 ) % 24;
		}

		if ( c_bmt_flash[i_bmt_flash] == '_' ) {
			zed_pass_use( texture_title_swat_city_0 );
			draw_title_layer();
		}

		zed_pass_use( texture_title_swat_city_1 );
		draw_title_layer();
		break;

		case chapter_blood_flush:        zed_pass_use( texture_title_blood_flush        ); draw_title_layer(); break;
		case chapter_cryoshock:          zed_pass_use( texture_title_cryoshock          ); draw_title_layer(); break;
		case chapter_full_metal_express: zed_pass_use( texture_title_full_metal_express ); draw_title_layer(); break;
		case chapter_gate_quake:         zed_pass_use( texture_title_gate_quake         ); draw_title_layer(); break;
		case chapter_hazard_company:     zed_pass_use( texture_title_hazard_company     ); draw_title_layer(); break;
		case chapter_horse_war:          zed_pass_use( texture_title_horse_war          ); draw_title_layer(); break;
		case chapter_howling_commandos:  zed_pass_use( texture_title_howling_commandos  ); draw_title_layer(); break;
		case chapter_plastic_platoon:    zed_pass_use( texture_title_plastic_platoon    ); draw_title_layer(); break;
		case chapter_primitive_streak:   zed_pass_use( texture_title_primitive_streak   ); draw_title_layer(); break;
		case chapter_route_66:           zed_pass_use( texture_title_route_66           ); draw_title_layer(); break;
		case chapter_threefold_path:     zed_pass_use( texture_title_threefold_path     ); draw_title_layer(); break;
	}
}

void draw_title_maze() {
	zed_canvas_fill( canvas_x1, color_maze_menu_bg );
	zed_pass_reset( pass_title );
	zed_pass_use( gfx_start_1984 );
	draw_title_layer();
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
		game_menu_page_none:
		return;

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
		default:
		draw_title();
		break;

		case game_menu_page_maze:
		draw_title_maze();
		break;
	}

	app_graphics_text_begin();
	game_menu_main( menu, game_menu_signal_render );
	app_graphics_text_finish();
}
