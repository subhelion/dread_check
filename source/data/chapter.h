#pragma once

enum game_chapter {
	chapter_none = 0,

	#define field( name ) chapter_##name,
	#include "chapter.inl"
	#undef field

	// chapter_alien_intel_classic,
	// chapter_alien_intel,
	// chapter_blood_flush,
	// chapter_blood_flush_vintage,
	// chapter_blue_monsoon,
	// chapter_cryoshock,
	// chapter_draugb,
	// chapter_full_metal_express,
	// chapter_gate_quake_classic,
	// chapter_gate_quake,
	// chapter_gate_quake_4000,
	// chapter_hazard_company,
	// chapter_horse_war,
	// chapter_horse_war_3000,
	// chapter_howling_commandos,
	// chapter_plastic_platoon,
	// chapter_primitive_streak,
	// chapter_red_cry,
	// chapter_route_66,
	// chapter_swat_city,
	// chapter_swat_city_300,
	// chapter_threefold_path,
	// chapter_wuerm_arctigeddon,
	// chapter_wuerm_arctigeddon_modern,

	chapter_max,
};

int chapter_current  = chapter_none;

// int chapter_continue = chapter_alien_intel;
// int chapter_continue = chapter_blue_monsoon;
// int chapter_continue = chapter_blood_flush;
// int chapter_continue = chapter_cryoshock;
// int chapter_continue = chapter_draugb;
// int chapter_continue = chapter_full_metal_express;
// int chapter_continue = chapter_gate_quake;
// int chapter_continue = chapter_hazard_company;
// int chapter_continue = chapter_horse_war;
// int chapter_continue = chapter_howling_commandos;
// int chapter_continue = chapter_plastic_platoon;
// int chapter_continue = chapter_primitive_streak;
// int chapter_continue = chapter_red_cry;
int chapter_continue = chapter_swat_city;
// int chapter_continue = chapter_swat_city_x;
// int chapter_continue = chapter_threefold_path;

void chapter_set( int chapter_new ) {
	if ( chapter_new == chapter_current ) return;
	// todo transition animation
	chapter_current = chapter_new;
}
