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

struct theme_t {
	uint color_bg;
	uint color_text_bg;
	uint color_text_fg;
	uint color_text_bg_active;
	uint color_text_fg_active;
};

theme_t theme[ chapter_max ];

// todo never called

void theme_init() {
	theme[ chapter_none                     ].color_bg             = 0xF7E658;
	theme[ chapter_none                     ].color_text_bg        = 0;
	theme[ chapter_none                     ].color_text_fg        = 0xBB007E;
	theme[ chapter_none                     ].color_text_bg_active = 0;
	theme[ chapter_none                     ].color_text_fg_active = 0xFFFFFF;

	theme[ chapter_alien_intel_classic      ].color_bg             = 0;
	theme[ chapter_alien_intel_classic      ].color_text_bg        = 0;
	theme[ chapter_alien_intel_classic      ].color_text_fg        = 0;
	theme[ chapter_alien_intel_classic      ].color_text_bg_active = 0;
	theme[ chapter_alien_intel_classic      ].color_text_fg_active = 0;

	theme[ chapter_alien_intel              ].color_bg             = 0;
	theme[ chapter_alien_intel              ].color_text_bg        = 0;
	theme[ chapter_alien_intel              ].color_text_fg        = 0;
	theme[ chapter_alien_intel              ].color_text_bg_active = 0;
	theme[ chapter_alien_intel              ].color_text_fg_active = 0;

	theme[ chapter_blood_flush              ].color_bg             = 0;
	theme[ chapter_blood_flush              ].color_text_bg        = 0;
	theme[ chapter_blood_flush              ].color_text_fg        = 0;
	theme[ chapter_blood_flush              ].color_text_bg_active = 0;
	theme[ chapter_blood_flush              ].color_text_fg_active = 0;

	theme[ chapter_blood_flush_vintage      ].color_bg             = 0;
	theme[ chapter_blood_flush_vintage      ].color_text_bg        = 0;
	theme[ chapter_blood_flush_vintage      ].color_text_fg        = 0;
	theme[ chapter_blood_flush_vintage      ].color_text_bg_active = 0;
	theme[ chapter_blood_flush_vintage      ].color_text_fg_active = 0;

	theme[ chapter_blue_monsoon             ].color_bg             = 0;
	theme[ chapter_blue_monsoon             ].color_text_bg        = 0;
	theme[ chapter_blue_monsoon             ].color_text_fg        = 0;
	theme[ chapter_blue_monsoon             ].color_text_bg_active = 0;
	theme[ chapter_blue_monsoon             ].color_text_fg_active = 0;

	theme[ chapter_cryoshock                ].color_bg             = 0;
	theme[ chapter_cryoshock                ].color_text_bg        = 0;
	theme[ chapter_cryoshock                ].color_text_fg        = 0;
	theme[ chapter_cryoshock                ].color_text_bg_active = 0;
	theme[ chapter_cryoshock                ].color_text_fg_active = 0;

	theme[ chapter_draugb                   ].color_bg             = 0;
	theme[ chapter_draugb                   ].color_text_bg        = 0;
	theme[ chapter_draugb                   ].color_text_fg        = 0;
	theme[ chapter_draugb                   ].color_text_bg_active = 0;
	theme[ chapter_draugb                   ].color_text_fg_active = 0;

	theme[ chapter_full_metal_express       ].color_bg             = 0;
	theme[ chapter_full_metal_express       ].color_text_bg        = 0;
	theme[ chapter_full_metal_express       ].color_text_fg        = 0;
	theme[ chapter_full_metal_express       ].color_text_bg_active = 0;
	theme[ chapter_full_metal_express       ].color_text_fg_active = 0;

	theme[ chapter_gate_quake_classic       ].color_bg             = 0;
	theme[ chapter_gate_quake_classic       ].color_text_bg        = 0;
	theme[ chapter_gate_quake_classic       ].color_text_fg        = 0;
	theme[ chapter_gate_quake_classic       ].color_text_bg_active = 0;
	theme[ chapter_gate_quake_classic       ].color_text_fg_active = 0;

	theme[ chapter_gate_quake               ].color_bg             = 0;
	theme[ chapter_gate_quake               ].color_text_bg        = 0;
	theme[ chapter_gate_quake               ].color_text_fg        = 0;
	theme[ chapter_gate_quake               ].color_text_bg_active = 0;
	theme[ chapter_gate_quake               ].color_text_fg_active = 0;

	theme[ chapter_gate_quake_4000          ].color_bg             = 0;
	theme[ chapter_gate_quake_4000          ].color_text_bg        = 0;
	theme[ chapter_gate_quake_4000          ].color_text_fg        = 0;
	theme[ chapter_gate_quake_4000          ].color_text_bg_active = 0;
	theme[ chapter_gate_quake_4000          ].color_text_fg_active = 0;

	theme[ chapter_hazard_company           ].color_bg             = 0;
	theme[ chapter_hazard_company           ].color_text_bg        = 0;
	theme[ chapter_hazard_company           ].color_text_fg        = 0;
	theme[ chapter_hazard_company           ].color_text_bg_active = 0;
	theme[ chapter_hazard_company           ].color_text_fg_active = 0;

	theme[ chapter_horse_war                ].color_bg             = 0;
	theme[ chapter_horse_war                ].color_text_bg        = 0;
	theme[ chapter_horse_war                ].color_text_fg        = 0;
	theme[ chapter_horse_war                ].color_text_bg_active = 0;
	theme[ chapter_horse_war                ].color_text_fg_active = 0;

	theme[ chapter_horse_war_3000           ].color_bg             = 0;
	theme[ chapter_horse_war_3000           ].color_text_bg        = 0;
	theme[ chapter_horse_war_3000           ].color_text_fg        = 0;
	theme[ chapter_horse_war_3000           ].color_text_bg_active = 0;
	theme[ chapter_horse_war_3000           ].color_text_fg_active = 0;

	theme[ chapter_howling_commandos        ].color_bg             = 0;
	theme[ chapter_howling_commandos        ].color_text_bg        = 0;
	theme[ chapter_howling_commandos        ].color_text_fg        = 0;
	theme[ chapter_howling_commandos        ].color_text_bg_active = 0;
	theme[ chapter_howling_commandos        ].color_text_fg_active = 0;

	theme[ chapter_plastic_platoon          ].color_bg             = 0;
	theme[ chapter_plastic_platoon          ].color_text_bg        = 0;
	theme[ chapter_plastic_platoon          ].color_text_fg        = 0;
	theme[ chapter_plastic_platoon          ].color_text_bg_active = 0;
	theme[ chapter_plastic_platoon          ].color_text_fg_active = 0;

	theme[ chapter_primitive_streak         ].color_bg             = 0;
	theme[ chapter_primitive_streak         ].color_text_bg        = 0;
	theme[ chapter_primitive_streak         ].color_text_fg        = 0;
	theme[ chapter_primitive_streak         ].color_text_bg_active = 0;
	theme[ chapter_primitive_streak         ].color_text_fg_active = 0;

	theme[ chapter_red_cry                  ].color_bg             = 0;
	theme[ chapter_red_cry                  ].color_text_bg        = 0;
	theme[ chapter_red_cry                  ].color_text_fg        = 0;
	theme[ chapter_red_cry                  ].color_text_bg_active = 0;
	theme[ chapter_red_cry                  ].color_text_fg_active = 0;

	theme[ chapter_route_66                 ].color_bg             = 0;
	theme[ chapter_route_66                 ].color_text_bg        = 0;
	theme[ chapter_route_66                 ].color_text_fg        = 0;
	theme[ chapter_route_66                 ].color_text_bg_active = 0;
	theme[ chapter_route_66                 ].color_text_fg_active = 0;

	theme[ chapter_swat_city                ].color_bg             = 0;
	theme[ chapter_swat_city                ].color_text_bg        = 0;
	theme[ chapter_swat_city                ].color_text_fg        = 0;
	theme[ chapter_swat_city                ].color_text_bg_active = 0;
	theme[ chapter_swat_city                ].color_text_fg_active = 0;

	theme[ chapter_swat_city_300            ].color_bg             = 0;
	theme[ chapter_swat_city_300            ].color_text_bg        = 0;
	theme[ chapter_swat_city_300            ].color_text_fg        = 0;
	theme[ chapter_swat_city_300            ].color_text_bg_active = 0;
	theme[ chapter_swat_city_300            ].color_text_fg_active = 0;

	theme[ chapter_threefold_path           ].color_bg             = 0;
	theme[ chapter_threefold_path           ].color_text_bg        = 0;
	theme[ chapter_threefold_path           ].color_text_fg        = 0;
	theme[ chapter_threefold_path           ].color_text_bg_active = 0;
	theme[ chapter_threefold_path           ].color_text_fg_active = 0;

	theme[ chapter_wuerm_arctigeddon        ].color_bg             = 0;
	theme[ chapter_wuerm_arctigeddon        ].color_text_bg        = 0;
	theme[ chapter_wuerm_arctigeddon        ].color_text_fg        = 0;
	theme[ chapter_wuerm_arctigeddon        ].color_text_bg_active = 0;
	theme[ chapter_wuerm_arctigeddon        ].color_text_fg_active = 0;

	theme[ chapter_wuerm_arctigeddon_modern ].color_bg             = 0;
	theme[ chapter_wuerm_arctigeddon_modern ].color_text_bg        = 0;
	theme[ chapter_wuerm_arctigeddon_modern ].color_text_fg        = 0;
	theme[ chapter_wuerm_arctigeddon_modern ].color_text_bg_active = 0;
	theme[ chapter_wuerm_arctigeddon_modern ].color_text_fg_active = 0;

}
