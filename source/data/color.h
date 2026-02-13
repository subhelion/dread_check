#pragma once
#pragma warning( disable : 4005 )

#include "chapter.h"

#define color_menu_fg        0xDDDDDD
#define color_menu_fg_active 0xFFCC44

#define color_hud_fg        0xDDDDCC
#define color_hud_fg_active 0xFFCC44

#define color_clay_bg        0x181818
#define color_clay_bg_hover  0x1F1F1F
#define color_clay_bg_active 0x353535
#define color_clay_fg        0xC5C5C5
#define color_clay_border    0x2B2B2B
#define color_clay_active    0x0078D7

#define color_ambient_0 0xFFFFE5

#define color_maze_menu_bg 0, 0, 170

#define color_main_fg 0xBB007E
#define color_main_bg 0xF7E658

uint get_color_fg() {
	// return color_menu_fg;
	// return 0x46FF81;
	if ( game.menu[0].state.page >= game_menu_page_options and game.menu[0].state.page <= game_menu_page_credits ) return color_main_bg;
	return color_main_fg;
}

uint get_color_fg( game_menu &menu, int id ) {
	uint color_active = color_menu_fg_active;
	uint color        = color_menu_fg;

	if ( chapter_current == chapter_none ) color_active = 0xFFFFFF; // color_main_fg_active;
	if ( chapter_current == chapter_none ) color        = color_main_fg;
	if ( game.menu[0].state.page >= game_menu_page_options and game.menu[0].state.page <= game_menu_page_credits ) color = color_main_bg;

	return menu.state.x == 0 and menu.state.y == id ? color_active : color;
}

uint get_color_fg( game_menu &menu, int id, bool which ) {
	uint color_active = 0xFFFFFF; // color_main_fg_active;
	uint color = which ? color_main_fg : color_main_bg;
	return menu.state.x == 0 and menu.state.y == id ? color_active : color;
}
