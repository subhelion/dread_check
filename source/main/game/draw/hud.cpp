#include "hud.h"

#include "../../game.h"
#include "../../game/player.h"

#include "hud/hands.cpp"
#include "hud/hint.cpp"
#include "hud/a.cpp"
#include "hud/b.cpp"
#include "hud/x.cpp"
#include "hud/y.cpp"

game_player_hint get_hint( game_player &player ) {
	game_player_hint hint = player.hint;

	if( hint == hint_none ) {
		switch ( player.stance ) {
			case stance_jog:    hint = hint_jog;    break;
			case stance_run:    hint = hint_run;    break;
			case stance_reach:  hint = hint_reach;  break;
			case stance_stalk:  hint = hint_stalk;  break;
			case stance_crouch: hint = hint_crouch; break;
			case stance_crawl:  hint = hint_crawl;  break;
			case stance_prone:  hint = hint_prone;  break;
			case stance_supine: hint = hint_supine; break;
			case stance_jump:   hint = hint_jump;   break;
			case stance_skid:   hint = hint_skid;   break;
			case stance_trip:   hint = hint_trip;   break;
			case stance_sail:   hint = hint_sail;   break;
			case stance_fall:   hint = hint_fall;   break;

			case stance_side_left:
			case stance_side_right:
			hint = hint_side;
			break;

			case stance_walk:
			if ( player.b_menu_handled ) hint = hint_stand;
			break;

			case stance_dive_prone:
			case stance_dive_supine:
			case stance_dive_left:
			case stance_dive_right:
			hint = hint_dive;
			break;

			case stance_slide_prone:
			case stance_slide_supine:
			case stance_slide_left:
			case stance_slide_right:
			hint = hint_slide;
			break;
		}

		if ( player.torso == torso_aim ) hint = hint_aim;
	}

	return hint;
}

string get_hint_text( game_player &player, game_player_hint player_hint) {
	game_item &item = game_player_hands_get_item( player );

	switch ( player_hint ) {
		case hint_reach:  return "REACH";
		case hint_stand:  return "STAND";
		case hint_stalk:  return "STALK";
		case hint_crouch: return "CROUCH";
		case hint_crawl:  return "CRAWL";
		case hint_prone:  return "PRONE";
		case hint_supine: return "SUPINE";
		case hint_side:   return "SIDE";
		case hint_jog:    return "JOG";
		case hint_run:    return "RUN";
		case hint_jump:   return "JUMP";
		case hint_fall:   return "FALL";
		case hint_sail:   return "CHUTE";
		case hint_skid:   return "SKID";
		case hint_dive:   return "DIVE";
		case hint_aim:    return item.type.i == item_none ? "WALK" : "AIM";
		case hint_load:   return "RELOAD";
		case hint_rack:   return "RACK";
		case hint_hold:   return "HOLD";
		case hint_grab:   return "GRAB";
		case hint_push:   return "PUSH";
		case hint_toss:   return "TOSS";

		case hint_a_menu: return "JUMP";
		case hint_x_menu: return game_item_can( item, action_reload ) ?  "RELOAD" : "--";

		// case hint_y_menu:
		// game_player player_copy = player;
		// game_player_hands_switch( player_copy, true );
		// return item_name[ game_player_hands_get_item( player_copy ).type.i ];
	}

	return "";
}

void game_draw_hud() {
	game_draw_set_camera_i {
		if ( game.menu[i].state.page != game_menu_page_none ) continue;
		game_player &player = game.data.player[i];
		game_item &item = game_player_hands_get_item( player );
		game_hud hud = {};

		app_graphics_text_begin();

		// todo
		hud_rect hud_rect_get();
		hud_rect r = hud_rect_get();
		// hud_text( "NOW PLAYING", r.x0, r.y0 );

		game_player_hint player_hint = get_hint( player );
		hud.text = get_hint_text( player, player_hint );
		if ( player.action == action_reload ) hud.text = "RELOAD";

		hud.x = canvas_x1.size.x / 2;
		hud.y = ( canvas_x1.size.y - 240 ) / 2 + 240 - 60;
		if ( split == game_split_duo ) hud.x = floor( hud.x / 2 );

		uint color = 0xffffff;
		if ( player.pad.w or player.pad.e or player.pad.n or player.pad.s or player.y_menu_handled ) color = 0xffffff; else color = 0xffcc44;

		switch ( player.hint ) {
			case hint_a_menu: game_draw_hud_a( player, hud ); break;
			case hint_b_menu: game_draw_hud_b( player, hud ); break;
			case hint_x_menu: game_draw_hud_x( player, hud ); break;
			case hint_y_menu: game_draw_hud_y( player, hud ); break;

			default:
			game_draw_hud_hands( player, hud );
			color = 0xffffff;
		}

		if ( hud.text   ) hud_text( hud.text,   hud.x, hud.y,      align_center, color );
		if ( hud.text_n ) hud_text( hud.text_n, hud.x, hud.y - 20, align_center, player.pad.n ? 0xffcc44 : 0xffffff );
		if ( hud.text_s ) hud_text( hud.text_s, hud.x, hud.y + 20, align_center, player.pad.s ? 0xffcc44 : 0xffffff );
		if ( hud.text_w ) hud_text( hud.text_w, hud.x - 70, hud.y, align_center, player.pad.w ? 0xffcc44 : 0xffffff );
		if ( hud.text_e ) hud_text( hud.text_e, hud.x + 70, hud.y, align_center, player.pad.e ? 0xffcc44 : 0xffffff );

		app_graphics_text_finish();
	}
}
