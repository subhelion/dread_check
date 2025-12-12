#pragma once

enum game_menu_page {
	game_menu_page_none = 0,
	game_menu_page_start,
	game_menu_page_play,
	game_menu_page_play_mode,
	game_menu_page_play_action,
	game_menu_page_play_action_channel,
	game_menu_page_play_adventure,
	game_menu_page_play_adventure_new,
	game_menu_page_play_adventure_load,
	game_menu_page_play_adventure_campaign,
	game_menu_page_play_adventure_chapter,
	game_menu_page_roster,
	game_menu_page_roster_character,
	game_menu_page_options,
	game_menu_page_options_input,
	game_menu_page_options_input_singleplayer,
	game_menu_page_options_input_multiplayer,
	game_menu_page_options_video,
	game_menu_page_options_audio,
	game_menu_page_options_data,
	game_menu_page_credits,
	game_menu_page_pause,

	game_menu_page_maze,
};

struct game_menu_state {
	game_menu_page page;
	int x, y;
};

enum game_menu_signal {
	game_menu_signal_none,
	game_menu_signal_render,
	game_menu_signal_select,
	game_menu_signal_hover,
	game_menu_signal_left,
	game_menu_signal_right,
};

struct game_menu {
	game_menu_state  state;
	game_menu_state  stack[16];
	int              i;
	game_menu_signal signal;
	int              j;
	game_menu_state  state_previous;
};

bool menu_did_back = false;
int local_player_count = 1;
char *name_campaign[] = { "Draugb" }; //, "Halo", "Half Life", "Quake", "Marathon", "Doom", "Wolfenstein" };
char *date_campaign[] = { "2020"   }; //, "2001", "1998",      "1996",  "1994",     "1993", "1992"        };
int menu_campaign_i = 0;
char *name_chapter[]  = { "Harbor", "Colony", "Frontier", "Wastes", "Tower", "Draugb" };
int menu_chapter_i  = 0;
int i_static_temp   = 0;
// char *name_privacy[] = { "Public", "Request", "Private", "Offline" };
char *name_privacy[] = { "Public", "Private", "Offline" };
int menu_privacy_i  = 0;
char *name_chat[] = { "Any", "Voice", "Text", "None" };
int menu_chat_i   = 0;
bool menu_status_offline = 0;
int menu_name_0_i = 202;
bool menu_roster_hover = false;
int menu_roster_hover_i = 0;
uint menu_roster_page = 0;
int menu_roster_field_i = 0;

int menu_character_0_i = 0;
int menu_character_1_i = 1;
int menu_character_2_i = 2;
int menu_character_3_i = 3;

int credits_page_i;
