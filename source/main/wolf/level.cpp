#include <zed/app/system.h>
#include <zed/xmath.h>

#include "../../main/game.h"
#include "../../main/game/player.h"
#include "../wolf.h"

float wolf_player_start_x;
float wolf_player_start_y;
float wolf_player_start_rotation;

void wolf_level_load( int level ) {
	int offset   = ( 17 + level * 10 + level * 64 * 64 * 3 ) * 2;
	// int offset_b = offset + 64 * 64 * 2;
	wolf.sprite_i = 0;

	zed_file file = app_system_fopen( "data/resources/id/wolf/all/map/wdc.map" );

	app_system_fseek( file, offset );

	char data[2] = {};

	for ( int i = 0; i < 64 * 64; i++ ) {
		int x = 63 - i % 64;
		int y = ( i - i % 64 ) / 64;
		int j = x + y * 64;
		app_system_fread( file, data, 2, 1 );
		wolf.grid[j].color = *(uint16_t *)data;
	}

	// app_system_fread( file, data, 2, 1 );

	for ( int i = 0; i < 64 * 64; i++ ) {
		app_system_fread( file, data, 2, 1 );
		int id = *(uint16_t *)data;

		int x = 63 - i % 64;
		int y = ( i - i % 64 ) / 64;
		int j = x + y * 64;

		float3 p = float3( x, 0, y );

		switch ( id ) {
			case wolf_object_start_n: wolf_player_start_x = x; wolf_player_start_y = y; wolf_player_start_rotation = 180; break;
			case wolf_object_start_e: wolf_player_start_x = x; wolf_player_start_y = y; wolf_player_start_rotation = 270; break;
			case wolf_object_start_s: wolf_player_start_x = x; wolf_player_start_y = y; wolf_player_start_rotation =   0; break;
			case wolf_object_start_w: wolf_player_start_x = x; wolf_player_start_y = y; wolf_player_start_rotation =  90; break;

			case wolf_object_pool_water   :
			case wolf_object_oil_drum     :
			case wolf_object_table_chairs :
			case wolf_object_floor_lamp   :
			case wolf_object_chandelier   :
			case wolf_object_skeleton_hang:
			case wolf_object_food_dog     :
			case wolf_object_column_white :
			case wolf_object_plant_green  :
			case wolf_object_skeleton     :
			case wolf_object_sink         :
			case wolf_object_plant_brown  :
			case wolf_object_vase         :
			case wolf_object_table        :
			case wolf_object_ceiling_light:
			case wolf_object_junk_brown   :
			case wolf_object_armor        :
			case wolf_object_cage_empty   :
			case wolf_object_cage_skeleton:
			case wolf_object_bones_0      :
			case wolf_object_key_gold     :
			case wolf_object_key_silver   :
			case wolf_object_bed          :
			case wolf_object_basket       :
			case wolf_object_food         :
			case wolf_object_ifak         :
			case wolf_object_ammo         :
			case wolf_object_gun_mach     :
			case wolf_object_gun_mini     :
			case wolf_object_loot_cross   :
			case wolf_object_loot_chalice :
			case wolf_object_loot_chest   :
			case wolf_object_loot_crown   :
			case wolf_object_extra_life   :
			case wolf_object_bones_blood  :
			case wolf_object_barrel       :
			case wolf_object_well_water   :
			case wolf_object_well_empty   :
			case wolf_object_pool_blood   :
			case wolf_object_flag         :
			case wolf_object_aardwolf     :
			case wolf_object_bones_1      :
			case wolf_object_bones_2      :
			case wolf_object_bones_3      :
			case wolf_object_junk_blue    :
			case wolf_object_stove        :
			case wolf_object_rack         :
			case wolf_object_vines        : wolf.sprite[ wolf.sprite_i++ ] = { p, id - 23 }; break;

			//

			case wolf_object_turn_e : wolf.grid[j].a = wolf_object_turn_e ; break;
			case wolf_object_turn_ne: wolf.grid[j].a = wolf_object_turn_ne; break;
			case wolf_object_turn_n : wolf.grid[j].a = wolf_object_turn_n ; break;
			case wolf_object_turn_nw: wolf.grid[j].a = wolf_object_turn_nw; break;
			case wolf_object_turn_w : wolf.grid[j].a = wolf_object_turn_w ; break;
			case wolf_object_turn_sw: wolf.grid[j].a = wolf_object_turn_sw; break;
			case wolf_object_turn_s : wolf.grid[j].a = wolf_object_turn_s ; break;
			case wolf_object_turn_se: wolf.grid[j].a = wolf_object_turn_se; break;

			//

			case wolf_object_door_secret:
				wolf.grid[j].s  = 1;
				break;

			case wolf_object_door_final : break;

			//

			case wolf_object_guard_dead      : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard, 0, frame_dead }; break;
			case wolf_object_guard_0_idle_e  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8e, 0 }; break;
			case wolf_object_guard_0_idle_n  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8n, 0 }; break;
			case wolf_object_guard_0_idle_w  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8w, 0 }; break;
			case wolf_object_guard_0_idle_s  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8s, 0 }; break;
			case wolf_object_guard_0_move_e  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8e, 1 }; break;
			case wolf_object_guard_0_move_n  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8n, 1 }; break;
			case wolf_object_guard_0_move_w  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8w, 1 }; break;
			case wolf_object_guard_0_move_s  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8s, 1 }; break;
			case wolf_object_officer_0_idle_e: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8e, 0 }; break;
			case wolf_object_officer_0_idle_n: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8n, 0 }; break;
			case wolf_object_officer_0_idle_w: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8w, 0 }; break;
			case wolf_object_officer_0_idle_s: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8s, 0 }; break;
			case wolf_object_officer_0_move_e: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8e, 1 }; break;
			case wolf_object_officer_0_move_n: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8n, 1 }; break;
			case wolf_object_officer_0_move_w: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8w, 1 }; break;
			case wolf_object_officer_0_move_s: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8s, 1 }; break;
			case wolf_object_ss_0_idle_e     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8e, 0 }; break;
			case wolf_object_ss_0_idle_n     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8n, 0 }; break;
			case wolf_object_ss_0_idle_w     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8w, 0 }; break;
			case wolf_object_ss_0_idle_s     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8s, 0 }; break;
			case wolf_object_ss_0_move_e     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8e, 1 }; break;
			case wolf_object_ss_0_move_n     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8n, 1 }; break;
			case wolf_object_ss_0_move_w     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8w, 1 }; break;
			case wolf_object_ss_0_move_s     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8s, 1 }; break;
			case wolf_object_dog_0_move_e    : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_dog,     wolf_8e, 1 }; break;
			case wolf_object_dog_0_move_n    : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_dog,     wolf_8n, 1 }; break;
			case wolf_object_dog_0_move_w    : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_dog,     wolf_8w, 1 }; break;
			case wolf_object_dog_0_move_s    : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_dog,     wolf_8s, 1 }; break;
			case wolf_object_guard_1_idle_e  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8e, 0 }; break;
			case wolf_object_guard_1_idle_n  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8n, 0 }; break;
			case wolf_object_guard_1_idle_w  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8w, 0 }; break;
			case wolf_object_guard_1_idle_s  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8s, 0 }; break;
			case wolf_object_guard_1_move_e  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8e, 1 }; break;
			case wolf_object_guard_1_move_n  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8n, 1 }; break;
			case wolf_object_guard_1_move_w  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8w, 1 }; break;
			case wolf_object_guard_1_move_s  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8s, 1 }; break;
			case wolf_object_officer_1_idle_e: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8e, 0 }; break;
			case wolf_object_officer_1_idle_n: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8n, 0 }; break;
			case wolf_object_officer_1_idle_w: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8w, 0 }; break;
			case wolf_object_officer_1_idle_s: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8s, 0 }; break;
			case wolf_object_officer_1_move_e: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8e, 1 }; break;
			case wolf_object_officer_1_move_n: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8n, 1 }; break;
			case wolf_object_officer_1_move_w: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8w, 1 }; break;
			case wolf_object_officer_1_move_s: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8s, 1 }; break;
			case wolf_object_ss_1_idle_e     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8e, 0 }; break;
			case wolf_object_ss_1_idle_n     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8n, 0 }; break;
			case wolf_object_ss_1_idle_w     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8w, 0 }; break;
			case wolf_object_ss_1_idle_s     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8s, 0 }; break;
			case wolf_object_ss_1_move_e     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8e, 1 }; break;
			case wolf_object_ss_1_move_n     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8n, 1 }; break;
			case wolf_object_ss_1_move_w     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8w, 1 }; break;
			case wolf_object_ss_1_move_s     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8s, 1 }; break;
			case wolf_object_dog_1_move_e    : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_dog,     wolf_8e, 1 }; break;
			case wolf_object_dog_1_move_n    : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_dog,     wolf_8n, 1 }; break;
			case wolf_object_dog_1_move_w    : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_dog,     wolf_8w, 1 }; break;
			case wolf_object_dog_1_move_s    : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_dog,     wolf_8s, 1 }; break;
			case wolf_object_guard_2_idle_e  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8e, 0 }; break;
			case wolf_object_guard_2_idle_n  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8n, 0 }; break;
			case wolf_object_guard_2_idle_w  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8w, 0 }; break;
			case wolf_object_guard_2_idle_s  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8s, 0 }; break;
			case wolf_object_guard_2_move_e  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8e, 1 }; break;
			case wolf_object_guard_2_move_n  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8n, 1 }; break;
			case wolf_object_guard_2_move_w  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8w, 1 }; break;
			case wolf_object_guard_2_move_s  : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_guard,   wolf_8s, 1 }; break;
			case wolf_object_officer_2_idle_e: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8e, 0 }; break;
			case wolf_object_officer_2_idle_n: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8n, 0 }; break;
			case wolf_object_officer_2_idle_w: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8w, 0 }; break;
			case wolf_object_officer_2_idle_s: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8s, 0 }; break;
			case wolf_object_officer_2_move_e: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8e, 1 }; break;
			case wolf_object_officer_2_move_n: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8n, 1 }; break;
			case wolf_object_officer_2_move_w: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8w, 1 }; break;
			case wolf_object_officer_2_move_s: wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_officer, wolf_8s, 1 }; break;
			case wolf_object_ss_2_idle_e     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8e, 0 }; break;
			case wolf_object_ss_2_idle_n     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8n, 0 }; break;
			case wolf_object_ss_2_idle_w     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8w, 0 }; break;
			case wolf_object_ss_2_idle_s     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8s, 0 }; break;
			case wolf_object_ss_2_move_e     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8e, 1 }; break;
			case wolf_object_ss_2_move_n     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8n, 1 }; break;
			case wolf_object_ss_2_move_w     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8w, 1 }; break;
			case wolf_object_ss_2_move_s     : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_ss,      wolf_8s, 1 }; break;
			case wolf_object_dog_2_move_e    : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_dog,     wolf_8e, 1 }; break;
			case wolf_object_dog_2_move_n    : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_dog,     wolf_8n, 1 }; break;
			case wolf_object_dog_2_move_w    : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_dog,     wolf_8w, 1 }; break;
			case wolf_object_dog_2_move_s    : wolf.enemy[ wolf.enemy_i ++ ] = { p + float3( 0.5, 0, 0.5 ), wolf_enemy_dog,     wolf_8s, 1 }; break;
		}
	}

	// wolf_pc.position = game.data.player[0].position + float3( -1, 0.4, 0.5 ) * wolf_scale;

	app_system_fclose( file );

	//

	bool found[64*64];

	for ( int i = 0; i < 64 * 64; i++ ) {
		// int x = i % 64;
		// int y = ( i - i % 64 ) / 64;

		int j[8];

		j[0] = i -  1;
		j[1] = i +  1;
		j[2] = i - 64;
		j[3] = i + 64;

		j[4] = i - 63;
		j[5] = i + 63;
		j[6] = i - 65;
		j[7] = i + 65;

		found[i] = false;

		if ( j[0] >       0 and wolf.grid[j[0]].color > 105 ) found[i] = true;
		if ( j[1] < 64 * 64 and wolf.grid[j[1]].color > 105 ) found[i] = true;
		if ( j[2] >       0 and wolf.grid[j[2]].color > 105 ) found[i] = true;
		if ( j[3] < 64 * 64 and wolf.grid[j[3]].color > 105 ) found[i] = true;

		if ( j[4] >       0 and wolf.grid[j[4]].color > 105 ) found[i] = true;
		if ( j[5] < 64 * 64 and wolf.grid[j[5]].color > 105 ) found[i] = true;
		if ( j[6] >       0 and wolf.grid[j[6]].color > 105 ) found[i] = true;
		if ( j[7] < 64 * 64 and wolf.grid[j[7]].color > 105 ) found[i] = true;
	}

	for ( int i = 0; i < 64 * 64; i++ ) {
		if ( not found[i] ) wolf.grid[i].color = 106;
	}
}
