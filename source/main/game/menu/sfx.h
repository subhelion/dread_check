#pragma once

#include "../../../data/sfx.h"

void menu_sfx_back () { zed_play_sound( sfx_menu_beep,   -10 ); }
void menu_sfx_stop () { zed_play_sound( sfx_menu_stop,   -10 ); }
void menu_sfx_start() { zed_play_sound( sfx_menu_start,  -10 ); }
void menu_sfx_dec  () { zed_play_sound( sfx_menu_down,   -10 ); }
void menu_sfx_inc  () { zed_play_sound( sfx_menu_up,     -10 ); }
void menu_sfx_enter() { zed_play_sound( sfx_menu_select, -10 ); }
void menu_sfx_hover() { zed_play_sound( sfx_menu_choice, -10 ); }
