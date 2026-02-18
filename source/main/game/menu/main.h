#pragma once

#include "main.h"

#include "../../../data/color.h"
#include "../../../data/gfx.h"
#include "../../canvas.h"
#include "../../game.h"
#include "../../game/roster.h"

#include <zed/app/graphics.h>

#include "../menu.h"

#include <zed.h>
#include <zed/app/ui.h>

#include "action.h"
#include "draw.h"

typedef void (*game_menu_cb_t)( game_menu &menu );

bool check_hover( int x, int y, int w, int h ) {
	int mx = floor( ui.event.mouse.x * canvas_x1.size.y / app.system.device_size.y );
	int my = floor( ui.event.mouse.y * canvas_x1.size.y / app.system.device_size.y );

	return mx > x and my > y and mx < x + w and my < y + h;
}

#define game_menu_cb []( game_menu &menu )

void game_menu_label( game_menu &menu, string text, float x, float y ) {
	if ( menu.signal == game_menu_signal_render ) app_graphics_draw_text_new( text, x, y, get_color_fg() );
}

void game_menu_item( game_menu &menu, string text, float x, float y, game_menu_cb_t action = {} ) {
	int id = menu.j ++;

	if ( menu.signal == game_menu_signal_render ) app_graphics_draw_text_new( text, x, y, get_color_fg( menu, id )  );
	if ( menu.signal == game_menu_signal_hover ) if ( check_hover( x, y, app_graphics_text_measure( text ), 20 ) ) { menu.state.x = 0; menu.state.y = id; }
	if ( menu.signal == game_menu_signal_select and action and menu.state.x == 0 and menu.state.y == id ) action( menu );
}

void game_menu_item_dread_check( game_menu &menu, string text, float x, float y, bool which, game_menu_cb_t action = {} ) {
	int id = menu.j ++;
	if ( chapter_current != chapter_none ) return;
	if ( menu.signal == game_menu_signal_render ) app_graphics_draw_text_new( text, x, y, get_color_fg( menu, id, which )  );
	if ( menu.signal == game_menu_signal_hover ) if ( check_hover( x, y, app_graphics_text_measure( text ), 20 ) ) { menu.state.x = 0; menu.state.y = id; }
	if ( menu.signal == game_menu_signal_select and action and menu.state.x == 0 and menu.state.y == id ) action( menu );
}

void game_menu_item_int( game_menu &menu, string text, float x, float y, game_menu_cb_t action_left, game_menu_cb_t action_right ) {
	int id = menu.j ++;
	if ( menu.signal == game_menu_signal_render ) app_graphics_draw_text_new( text, x, y, get_color_fg( menu, id ) );
	if ( menu.signal == game_menu_signal_hover ) if ( check_hover( x, y, app_graphics_text_measure( text ), 20 ) ) { menu.state.x = 0; menu.state.y = id; }
	if ( menu.signal == game_menu_signal_left  and action_left  and menu.state.x == 0 and menu.state.y == id ) action_left ( menu );
	if ( menu.signal == game_menu_signal_right and action_right and menu.state.x == 0 and menu.state.y == id ) action_right( menu );
}

void game_menu_item_back( game_menu &menu, float x, float y ) {
	game_menu_item( menu, "Back", x, y, game_menu_cb { game_menu_action_back( menu ); });
}

void game_menu_item_continue( game_menu &menu, float x, float y ) {
	game_menu_item( menu, "Continue", x, y, game_menu_cb { game_menu_action_start_game_1p( menu ); });
	if ( menu.state.x == 0 and menu.state.y == menu.j - 1 ) chapter_set( chapter_continue ); else chapter_set( chapter_none );
}

void game_menu_item_status( game_menu &menu, float x, float y ) {
	if ( true ) {
		game_menu_label( menu, "Gamepad detected", x, y );
	} else {
		game_menu_label( menu, "Gamepad recommended", x, y );
	}

	game_menu_item( menu, name_status[menu_status_i], x, y + 20, game_menu_cb { toggle_status(); });
}

void game_menu_item_face( game_menu &menu, float x, float y, game_menu_cb_t action = {} ) {
	y += 4;

	int id = menu.j ++;

	int w = 64;
	int h = 64;

	if ( menu.signal == game_menu_signal_render ) {
		zed_pass_reset( pass_title );

		zed_draw_image( gfx_face[ roster[ i_static_temp ].face_i ], x + 64 * 0, y );

		if ( menu.state.x == 0 and menu.state.y == id ) {
			zed_draw_rect_empty( x, y, w, h, get_color_fg( menu, id ), 2 );
		}
	}

	if ( menu.signal == game_menu_signal_hover ) if ( check_hover( x, y, w, h ) ) { menu.state.x = 0; menu.state.y = id; menu_roster_hover = true; menu_roster_hover_i = i_static_temp; }
	if ( menu.signal == game_menu_signal_select and action and menu.state.x == 0 and menu.state.y == id ) action( menu );
}

void game_menu_item_squad( game_menu &menu, float x, float y ) {
	y += 4;

	int id = menu.j ++;

	int w = 64 * local_player_count;
	int h = 64;

	if ( menu.signal == game_menu_signal_render ) {
		zed_pass_reset( pass_title );

		if ( local_player_count >= 1 ) zed_draw_image( gfx_face[ roster[ menu_character_0_i ].face_i ], x + 64 * 0, y );
		if ( local_player_count >= 2 ) zed_draw_image( gfx_face[ roster[ menu_character_1_i ].face_i ], x + 64 * 1, y );
		if ( local_player_count >= 3 ) zed_draw_image( gfx_face[ roster[ menu_character_2_i ].face_i ], x + 64 * 2, y );
		if ( local_player_count == 4 ) zed_draw_image( gfx_face[ roster[ menu_character_3_i ].face_i ], x + 64 * 3, y );

		if ( menu.state.x == 0 and menu.state.y == id ) {
			zed_draw_rect_empty( x, y, w, h, get_color_fg( menu, id ), 2 );
		}
	}

	if ( menu.signal == game_menu_signal_hover  ) if ( check_hover( x, y, w, h ) ) { menu.state.x = 0; menu.state.y = id; }

	game_menu_cb_t action = game_menu_cb { game_menu_push( menu, game_menu_page_roster ); menu_roster_page = 0; game_roster_init( menu_roster_page ); };

	if ( menu.signal == game_menu_signal_select and action and menu.state.x == 0 and menu.state.y == id ) action( menu );
}

void game_menu_item_pc( game_menu &menu, float x, float y, float w, float h, game_menu_cb_t action = {} ) {
	y += 4;

	int id = menu.j ++;

	if ( menu.signal == game_menu_signal_render ) {
		zed_pass_reset( pass_title );

		if ( menu.state.x == 0 and menu.state.y == id ) {
			zed_draw_rect_empty( x, y, w, h, get_color_fg( menu, id ), 2 );
		}
	}

	if ( menu.signal == game_menu_signal_hover ) if ( check_hover( x, y, w, h ) ) { menu.state.x = 0; menu.state.y = id; }
	if ( menu.signal == game_menu_signal_select and action and menu.state.x == 0 and menu.state.y == id ) action( menu );
}
