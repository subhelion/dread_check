#pragma once

enum game_menu_page {
	game_menu_page_none = 0,
	game_menu_page_start,

	game_menu_page_play,
	game_menu_page_play_mode,
	game_menu_page_play_max,

	game_menu_page_play_action,
	game_menu_page_play_action_channel,
	game_menu_page_play_action_max,

	game_menu_page_play_adventure,
	game_menu_page_play_adventure_new,
	game_menu_page_play_adventure_max,

	game_menu_page_play_adventure_find,
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
	game_menu_page_options_max,

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

//, "Halo", "Half Life", "Quake", "Marathon", "Doom", "Wolfenstein" };
//, "2001", "1998",      "1996",  "1994",     "1993", "1992"        };

// XXXXX deep future
//  4XXX far future "4000"
//  3XXX far future "3000"
//  2XXX far future "2000"
//  21XX near future
//  20XX modern
//  19XX classic
//  1XXX vintage
//  0XXX ancient
// 0XXXX fossil

//	"Alien Intel 3000"          " 3XXX",
//	"Blood Flush 2000"          " 2XXX",
//	"Blood Flush 4000"          " 4XXX",
//	"Cold Hauler Buffalo",      " 4XXX",
//	"Concrete Jungle Fossil",   " 0XXX",
//	"Concrete Jungle",          " 21XX",
//	"Concrete Jungle 3000",     " 3XXX",
//	"Draugb 0. Prologue",       " 20XX",
//	"Draugb 1. Harbor",         " 19XX",
//	"Draugb 2. Colony",         " 21XX",
//	"Draugb 3. Frontier",       " 2XXX",
//	"Draugb 4. Wastes",         " 4XXX",
//	"Draugb 5. Tower",          "XXXXX",
//	"Draugb 6. Draugb",         "0XXXX",
//	"Horse War Classic",        " 19XX",
//	"Howling Commandos Modern", " 20XX",
//  "Untitled 1XXX",            " 1XXX", // tyrant engine crossover

char *data_campaign[] = {
	"Alien Intel Classic",      " 19XX",
	"Alien Intel",              " 21XX",
	"Blood Flush Vintage",      " 1XXX",
	"Blood Flush",              " 20XX",
	"Blue Monsoon",             " 19XX",
	"Cryoshock",                " 2XXX",
	"DRAUGB",                   "XXXXX",
	"Full Metal Express",       " 1XXX",
	"Gate Quake Classic",       " 19XX",
	"Gate Quake",               " 2XXX",
	"Gate Quake 4000",          " 4XXX",
	"Hazard Company",           " 3XXX",
	"Horse War",                " 21XX",
	"Horse War 3000",           " 3XXX",
	"Howling Commandos",        " 19XX",
	"Plastic Platoon",          " 2XXX",
	"Primitive Streak",         "XXXXX",
	"Red Cry",                  " 3XXX",
 // "Red Cry",                  "0XXXX",
	"Route 66",                 " 19XX",
	"Swat City",                " 2XXX",
	"Swat City 3000",           " 3XXX",
	"Threefold Path",           " 21XX",
	"Wuerm Arctigeddon",        " 0XXX",
	"Wuerm Arctigeddon Modern", " 20XX",
};

char *data_campaign_by_era[] = {
	"Red Cry",                 "0XXXX",
	"Würm Arctigeddon",        " 0XXX",
	"Blood Flush Vintage",     " 1XXX",
	"Full Metal Express",      " 1XXX",
	"Alien Intel Classic",     " 19XX",
	"Blue Monsoon",            " 19XX",
	"Gate Quake Classic",      " 19XX",
	"Howling Commandos",       " 19XX",
	"Route 66",                " 19XX",
	"Blood Flush",             " 20XX",
	"Würm Arctigeddon Modern", " 20XX",
	"Alien Intel",             " 21XX",
	"Horse War",               " 21XX",
	"Threefold Path",          " 21XX",
	"Cryoshock"                " 2XXX",
	"Gate Quake",              " 2XXX",
	"Plastic Platoon",         " 2XXX",
	"Swat City",               " 2XXX",
	"Hazard Company",          " 3XXX",
	"Horse War 3000",          " 3XXX",
	"Red Cry",                 " 3XXX",
	"Swat City 3000",          " 3XXX",
	"Gate Quake 4000",         " 4XXX",
	"DRAUGB",                  "XXXXX",
	"Primitive Streak",        "XXXXX",
};

char *name_campaign[] = {
	"Alien Intel Classic",
	"Alien Intel",
	"Blood Flush Vintage",
	"Blood Flush",
	"Blue Monsoon",
	"Cryoshock",
	"DRAUGB",
	"Full Metal Express",
	"Gate Quake Classic",
	"Gate Quake",
	"Gate Quake 4000",
	"Hazard Company",
	"Horse War",
	"Horse War 3000",
	"Howling Commandos",
	"Plastic Platoon",
	"Primitive Streak",
	"Red Cry",
	"Route 66",
	"Swat City",
	"Swat City 3000",
	"Threefold Path",
	"Wuerm Arctigeddon",
	"Wuerm Arctigeddon Modern",
};

char *era_campaign[] = {
	" 19XX",
	" 21XX",
	" 1XXX",
	" 20XX",
	" 19XX",
	" 2XXX",
	"XXXXX",
	" 1XXX",
	" 19XX",
	" 2XXX",
	" 4XXX",
	" 3XXX",
	" 21XX",
	" 3XXX",
	" 19XX",
	" 2XXX",
	"XXXXX",
	" 3XXX",
 // "0XXXX",
	" 19XX",
	" 2XXX",
	" 3XXX",
	" 21XX",
	" 0XXX",
	" 20XX",
};

int menu_campaign_i = 0;

char *name_chapter[]  = { "Harbor", "Colony", "Frontier", "Wastes", "Tower", "Draugb" };
int menu_chapter_i  = 0;

int i_static_temp   = 0;

// char *name_privacy[] = { "Public", "Request", "Private", "Offline" };
char *name_privacy[] = { "Public", "Private", "Offline" };
int menu_privacy_i  = 0;

char *name_chat[] = { "Any", "Voice", "Text", "None" };
int menu_chat_i   = 0;

char *name_status[] = { "Online", "LAN", "Offline" };
int menu_status_i = 0;

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
