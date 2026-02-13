#pragma once

#include "../menu.h"
#include "../menu/sfx.h"

void scene_game_start_for_real();

void game_menu_push( game_menu &menu, game_menu_page page ) {
	menu.stack[ menu.i ++ ] = menu.state;
	menu.state = {};
	menu.state.page = page;

	if ( game.has_mouse ) {
		menu.state.x = -1;
		menu.state.y = -1;

		void game_menu_main( game_menu &menu, game_menu_signal signal );
		game_menu_main( menu, game_menu_signal_hover );
	}
}

void game_menu_pop( game_menu &menu ) {
	menu.i --;
	menu.state.page = menu.stack[ menu.i ].page;
	menu.state.x    = menu.stack[ menu.i ].x;
	menu.state.y    = menu.stack[ menu.i ].y;

	if ( game.has_mouse ) {
		menu.state.x = -1;
		menu.state.y = -1;
	}
}

//

void game_menu_hide_mouse() {
	use_mouse = false;
	game_cursor_hide();

	if ( game.menu[0].state.x == -1 ) {
		game.menu[0].state.x = 0;
		game.menu[0].state.y = 0;
	}

	game.has_mouse = false;
}

void game_menu_action_start_game_1p( game_menu &menu ) {
	game_menu_hide_mouse();
	menu.state.page = game_menu_page_none;
	menu.i = 0;
	split = game_split_solo;
	game.player_count = 1;
	if ( game.scene == scene_game ) scene_game_start_for_real();
}

void game_menu_action_start_game_2p( game_menu &menu ) {
	game_menu_hide_mouse();
	menu.state.page = game_menu_page_none;
	menu.i = 0;
	split = game_split_duo;
	game.player_count = 2;
	if ( game.scene == scene_game ) scene_game_start_for_real();
}

void game_menu_action_start_game_3p( game_menu &menu ) {
	game_menu_hide_mouse();
	menu.state.page = game_menu_page_none;
	menu.i = 0;
	split = game_split_trio;
	game.player_count = 3;
	if ( game.scene == scene_game ) scene_game_start_for_real();
}

void game_menu_action_start_game_4p( game_menu &menu ) {
	game_menu_hide_mouse();
	menu.state.page = game_menu_page_none;
	menu.i = 0;
	split = game_split_quad;
	game.player_count = 4;
	if ( game.scene == scene_game ) scene_game_start_for_real();
}

void game_menu_action_start_maze_1p( game_menu &menu ) {
	game.is_started = true;
	game_menu_action_start_game_1p( menu );
	maze_start();
}

void game_menu_action_start_maze_2p( game_menu &menu ) {
	game.is_started = true;
	game_menu_action_start_game_2p( menu );
	maze_start();
}

void game_menu_resume( game_menu &menu ) {
	menu.state.page = game_menu_page_none;
	game.is_paused = false;
	game_cursor_hide();
}

void game_menu_action_back( game_menu &menu ) {
	if ( menu.state.page == game_menu_page_maze  ) { void scene_game_start(); scene_game_start(); game.scene = scene_game; }
	if ( menu.state.page == game_menu_page_start ) return;
	if ( menu.state.page == game_menu_page_pause ) { game_menu_resume( menu ); return; }
	if ( menu.i == 0 ) return;
	game_menu_pop( menu );
	menu_sfx_back();
	menu_did_back = true;
}

void game_menu_game_start( game_menu &menu ) {
	game.is_started = true;

	switch ( local_player_count ) {
		case 1: game_menu_action_start_game_1p( menu ); break;
		case 2: game_menu_action_start_game_2p( menu ); break;
		case 3: game_menu_action_start_game_3p( menu ); break;
		case 4: game_menu_action_start_game_4p( menu ); break;
	}
}

void toggle_status() {
	menu_status_offline = ! menu_status_offline;

	if ( menu_status_offline ) { menu_sfx_stop(); } else { menu_sfx_start(); }
}

void game_menu_roster_recruit() {
	menu_roster_page += 1;
	game_roster_init( menu_roster_page );
}

void game_menu_respawn( game_menu &menu ) {

}

void game_menu_adventure_find_refresh() {

}
