#include "../../../data/sfx.h"
#include "../player.h"

#include <zed.h>
#include <zed/app.h>

void game_bullet_make        ( game_player & );
bool game_player_stance_relax( game_player & );
void game_player_torso_relax ( game_player & );

int gun_capacity = 5;

void game_item_init() {
	item_mass_by_kind[ item_kind_hand  ].stiffness = 0.40;
	item_mass_by_kind[ item_kind_hand  ].damping   = 0.80;
	item_mass_by_kind[ item_kind_long  ].stiffness = 0.10;
	item_mass_by_kind[ item_kind_long  ].damping   = 0.20;
	item_mass_by_kind[ item_kind_heavy ].stiffness = 0.06;
	item_mass_by_kind[ item_kind_heavy ].damping   = 0.10;

	item_name[ item_none    ] = "HAND";  item_type[ item_none    ].kind = item_kind_hand;
	item_name[ item_bag     ] = "BAG";   item_type[ item_bag     ].kind = item_kind_heavy;
	item_name[ item_ammo    ] = "AMMO";  item_type[ item_ammo    ].kind = item_kind_hand;
	item_name[ item_torch   ] = "LIGHT"; item_type[ item_torch   ].kind = item_kind_hand;
	item_name[ item_sword   ] = "KNIFE"; item_type[ item_sword   ].kind = item_kind_hand;
	item_name[ item_grenade ] = "FRAG";  item_type[ item_grenade ].kind = item_kind_hand;

	item_name[ item_us_1917_revolver ]      = "R1917";
	item_type[ item_us_1917_revolver ].kind = item_kind_hand;
	item_type[ item_us_1917_revolver ].ammo = ammo_45acp;

	item_name[ item_wi_1897_shotgun  ]      = "S1897";
	item_type[ item_wi_1897_shotgun  ].i    = item_wi_1897_shotgun;
	item_type[ item_wi_1897_shotgun  ].kind = item_kind_long;
	item_type[ item_wi_1897_shotgun  ].mass = item_mass_by_kind[ item_kind_long ];
	item_type[ item_wi_1897_shotgun  ].ammo = ammo_12ga_slug;

	item_name[ item_ak_1947 ]      = "AK47";
	item_type[ item_ak_1947 ].i    = item_ak_1947;
	item_type[ item_ak_1947 ].kind = item_kind_long;
	item_type[ item_ak_1947 ].mass = item_mass_by_kind[ item_kind_long ];
	item_type[ item_ak_1947 ].ammo = ammo_762_39mm;

	item_name[ item_us_1919_bmg ]      = "B1919";
	item_type[ item_us_1919_bmg ].i    = item_us_1919_bmg;
	item_type[ item_us_1919_bmg ].kind = item_kind_heavy;
	item_type[ item_us_1919_bmg ].mass = item_mass_by_kind[ item_kind_heavy ];
	item_type[ item_us_1919_bmg ].ammo = ammo_762_63mm;

	for ( int i = 0; i < item_max; i++ ) {
		item_type[i].i = (game_item_i)i;
		item_type[i].mass = item_mass_by_kind[ item_type[i].kind ];
	}
}

bool game_item_can( game_item item, game_action action ) {
	switch( item.type.i ) {
		case item_none:
		return false;

		case item_torch:
		case item_sword:

		switch ( action ) {
			case action_shoot:
			case action_unshoot:
			return true;

			case action_slide_open:
			case action_slide_close:
			case action_reload:
			case action_unload:
			return false;
		}

		break;

		case item_us_1917_revolver:

		switch ( action ) {
			case action_shoot:
			case action_reload:
			return true;

			case action_slide_open:
			return not ( item.slide == slide_open  );

			case action_slide_close:
			return not ( item.slide == slide_close );

			case action_unshoot:
			case action_unload:
			return false;
		}

		break;

		case item_wi_1897_shotgun:
		case item_ak_1947:
		case item_us_1919_bmg:

		switch ( action ) {
			case action_shoot:
			case action_slide_open:
			return not ( item.slide == slide_open  );

			case action_slide_close:
			return not ( item.slide == slide_close );

			case action_reload:
			if ( item.slide == slide_open and item.chamber == chamber_empty ) return true;
			if ( item.magazine.count < gun_capacity ) return true;
			return false;

			case action_unshoot:
			case action_unload:
			return false;
		}

		break;
	}

	return true;
}

uint get_duration_for_action( game_item &item, game_action action ) {
	switch( action ) {
		case action_none: return 0;
		case action_grab: return 90;
		case action_push: return 90;
		case action_throw: return 90;
	}

	switch ( item.type.i ) {
		case item_none:
		case item_torch:
		break;

		case item_sword:
		return 10;
		break;

		case item_us_1917_revolver:

		switch( action ) {
			case action_shoot:       return 10;
			case action_slide_open:  return 1;
			case action_slide_close: return 1;
			case action_reload:      return 60;
		}

		break;

		case item_wi_1897_shotgun:
		case item_ak_1947:
		case item_us_1919_bmg:

		switch( action ) {
			case action_shoot:       return 5;
			case action_slide_open:  return 9;
			case action_slide_close: return 1;
			case action_reload:      return 30;
		}

		break;

	}

	return 1;
}

void flush_action_queue( game_player &player ) {
	player.action_queue_length = 0;
}

void game_item_sfx_fire( game_item &item ) {
	switch ( item.type.i ) {
		case item_none:
		break;

		case item_torch:
		zed_play_sound( sfx_light, -10 );
		break;

		case item_sword:
		zed_play_sound( sfx_knife, -10 );
		break;

		case item_us_1917_revolver:
		zed_play_sound( sfx_revolver_fire, -10 );
		break;

		case item_wi_1897_shotgun:
		case item_ak_1947:
		case item_us_1919_bmg:
		zed_play_sound( sfx_shotgun_fire, -10 );
		break;
	}
}

void game_item_sfx_dry   () { zed_play_sound( sfx_dry,           -30 ); }
void game_item_sfx_rack  () { zed_play_sound( sfx_shotgun_open,  -15 ); }
void game_item_sfx_unrack() { zed_play_sound( sfx_shotgun_close, -15 ); }
void game_item_sfx_load  () { zed_play_sound( sfx_shotgun_load,  -15 ); }

void game_item_fire( game_player &player ) {
	game_item &item = game_player_hands_get_item( player );
	if ( game_player_stance_relax( player ) ) return;
	player.action       = action_shoot;
	player.action_timer = get_duration_for_action( item, action_shoot );

	switch( item.type.i ) {
		case item_none:
		break;

		case item_torch:
		game_item_sfx_fire( item );
		return;
		break;

		case item_sword:
		break;

		case item_us_1917_revolver:

		if ( item.magazine.count == 0 ) {
			game_item_sfx_dry();
			return;
		}

		item.magazine.count -= 1;
		break;

		case item_wi_1897_shotgun:
		case item_ak_1947:
		case item_us_1919_bmg:

		if ( item.slide != slide_close or item.chamber != chamber_ready ) {
			game_item_sfx_dry();
			return;
		}

		item.chamber = chamber_spent;
		break;
	}

	game_item_sfx_fire( item );
	float recoil = 10;
	if ( player.torso == torso_aim ) recoil = 4;
	player.rig.recoil_0 = recoil;
	if ( item.type.i == item_sword ) return;
	player.gun_rig_0.rotation.x -= recoil;
	game_bullet_make( player );
}

void game_item_fire_offhand( game_player &player ) {
	game_item &item = player.hands.belt[ player.hands.k ];

	// todo
	player.action       = action_shoot;
	player.action_timer = get_duration_for_action( item, action_shoot );

	switch( item.type.i ) {
		case item_none:
		break;

		case item_torch:
		game_item_sfx_fire( item );
		return;
		break;

		case item_sword:
		break;

		case item_us_1917_revolver:

		if ( item.magazine.count == 0 ) {
			game_item_sfx_dry();
			return;
		}

		item.magazine.count -= 1;
		break;

		case item_wi_1897_shotgun:
		case item_ak_1947:
		case item_us_1919_bmg:

		if ( item.slide != slide_close or item.chamber != chamber_ready ) {
			game_item_sfx_dry();
			return;
		}

		item.chamber = chamber_spent;
		break;
	}

	game_item_sfx_fire( item );
	float recoil = 10;
	if ( player.torso == torso_aim ) recoil = 4;
	player.rig.recoil_1 = recoil;
	if ( item.type.i == item_sword ) return;
	player.gun_rig_1.rotation.x -= recoil;
	game_bullet_make( player );
}


void game_item_slide_open( game_player &player ) {
	game_item &item = game_player_hands_get_item( player );
	game_player_stance_relax( player );
	player.action       = action_slide_open;
	player.action_timer = get_duration_for_action( item, action_slide_open );
	game_item_sfx_rack();
	player.hint = hint_rack;
	item.chamber = chamber_empty;
}

void game_item_slide_close( game_player &player ) {
	game_item &item = game_player_hands_get_item( player );
	game_player_stance_relax( player );
	player.action       = action_slide_close;
	player.action_timer = get_duration_for_action( item, action_slide_close );
	game_item_sfx_unrack();
	if ( player.hint == hint_rack ) player.hint = hint_none;
}

void game_item_reload( game_player &player ) {
	game_item &item = game_player_hands_get_item( player );
	game_player_stance_relax( player );
	if ( player.stance == stance_jog ) player.stance = stance_walk;

	if ( item.slide == slide_open and item.chamber == chamber_empty ) {
		// note chamber reload doesn't lower aim
	} else {
		if ( player.torso == torso_aim ) player.torso = torso_hip;
	}

	player.action       = action_reload;
	player.action_timer = get_duration_for_action( item, action_reload );
	game_item_sfx_load();

	switch( item.type.i ) {
		case item_none:
		case item_torch:
		case item_sword:
		break;

		case item_us_1917_revolver:
		item.magazine.count = 0;
		player.bag.ammo[ player.ammo_i ] -= 6;
		break;

		case item_wi_1897_shotgun:
		case item_ak_1947:
		case item_us_1919_bmg:

		player.bag.ammo[ player.ammo_i ] -= 1;

		if ( item.slide == slide_open and item.chamber == chamber_empty ) {
			item.chamber = chamber_ready;
		} else {
			item.magazine.count += 1;
		}

		break;
	}
}

void game_item_do( game_player &player, game_action action ) {
	switch( action ) {
		case action_shoot:       game_item_fire       ( player ); break;
		case action_slide_open:  game_item_slide_open ( player ); break;
		case action_slide_close: game_item_slide_close( player ); break;
		case action_reload:      game_item_reload     ( player ); break;
	}
}

void game_item_finish( game_player &player, game_item &item, game_action, bool );

void game_item_try( game_player &player, game_action action ) {
	switch ( player.stance ) {
		case stance_jump:
		case stance_fall:
		case stance_sail:
		case stance_dive_prone:
		case stance_dive_supine:
		case stance_dive_left:
		case stance_dive_right:
		return;
	}

	game_item &item = game_player_hands_get_item( player );

	if ( player.action == action_none ) {
		if ( game_item_can( item, action ) ) game_item_do( player, action );
	} else {
		if ( player.action_queue_length < 8 ) {
			game_item item_copy = item;
			game_item_finish( player, item_copy, player.action, true );

			if ( player.action_queue_length > 0 ) {
				for ( uint i = 0; i < player.action_queue_length; i++ ) {
					game_item_finish( player, item_copy, player.action_queue[i], true );
				}
			}

			if ( game_item_can( item_copy, action ) ) {
				player.action_queue[player.action_queue_length] = action;
				player.action_queue_length += 1;
			}
		}
	}
}

void game_item_rack( game_item &item, bool silent ) {
	item.slide = slide_open;

	if ( item.chamber != chamber_empty ) {
		if ( not silent ) zed_play_sound( sfx_shell, -30 );
	}
}

void game_item_unrack( game_item &item, bool silent ) {
	switch( item.type.i ) {
		case item_none:
		case item_torch:
		case item_sword:
		case item_us_1917_revolver:
		break;

		case item_wi_1897_shotgun:
		case item_ak_1947:
		case item_us_1919_bmg:
		item.slide = slide_close;

		if ( item.chamber == chamber_empty ) {
			if ( item.magazine.count > 0 ) {
				item.magazine.count -= 1;
				item.chamber = chamber_ready;
			}
		}

		break;
	}
}

void game_item_reload( game_item &item, bool silent ) {
	switch( item.type.i ) {
		case item_none:
		case item_torch:
		case item_sword:
		break;

		case item_us_1917_revolver:
		item.magazine.count = 6;
		break;

		case item_wi_1897_shotgun:
		case item_ak_1947:
		case item_us_1919_bmg:
		break;
	}
}

int time_slide_open = 0;

void game_item_finish( game_player &player, game_item &item, game_action action, bool silent = false ) {
	switch( item.type.i ) {
		case item_none:
		case item_torch:
		case item_sword:
		break;

		case item_us_1917_revolver:

		switch ( action ) {
			case action_shoot:
			item.chamber = chamber_ready;
			break;

			case action_slide_open:
			item.chamber = chamber_ready;
			game_item_rack( item, silent );
			if ( not silent ) time_slide_open = app.time;
			break;

			case action_slide_close:
			game_item_unrack( item, silent );
			if ( player.trigger == 1.0 ) if ( not silent ) { game_player_torso_relax( player ); game_item_fire( player ); }
			break;

			case action_reload:
			game_item_reload( item, silent );
			break;
		}

		break;

		case item_wi_1897_shotgun:
		case item_ak_1947:
		case item_us_1919_bmg:

		switch ( action ) {
			case action_slide_open:
			game_item_rack( item, silent );
			break;

			case action_slide_close:
			game_item_unrack( item, silent );
			if ( not silent ) if ( player.trigger == 1.0 ) game_item_fire( player );
			break;

			case action_reload:
			game_item_reload( item, silent );
			if ( not silent ) if ( player.action_queue_length == 0 ) if ( player.bag.ammo[ player.ammo_i ] > 0 ) game_item_try( player, action_reload );
			break;
		}

		break;
	}
}

//


void game_player_queue_step( game_player &player ) {
	game_item &item = game_player_hands_get_item( player );

	if ( player.action != action_reload and not ( player.action_queue_length > 0 and player.action_queue[0] == action_reload ) ) {
		player.rig.reload = 0;
	}

	if ( player.action_timer > 0 ) {
		player.action_timer -= 1;

		if ( player.action == action_reload ) {
			float delta = 0.25;
			if ( player.rig.reload < 1 ) player.rig.reload += delta;
			if ( player.rig.reload > 1 ) player.rig.reload = 1.0;
		}

		if ( player.action_timer == 0 ) {
			game_item_finish( player, item, player.action );
			player.action = action_none;
		}
	} else {
		if ( player.action == action_none ) {
			if ( player.action_queue_length > 0 ) {
				game_item_do( player, player.action_queue[0] );

				player.action_queue[0] = player.action_queue[1];
				player.action_queue[1] = player.action_queue[2];
				player.action_queue[2] = player.action_queue[3];
				player.action_queue[3] = player.action_queue[4];
				player.action_queue[4] = player.action_queue[5];
				player.action_queue[5] = player.action_queue[6];
				player.action_queue[6] = player.action_queue[7];
				player.action_queue[7] = action_none;

				player.action_queue_length -= 1;
			}
		}
	}
}

void game_player_queue_interrupt( game_player &player ) {
	switch( player.action ) {
		// todo
	}

	player.action = action_none;
	player.action_queue_length = 0;

	player.action_queue[0] = action_none;
	player.action_queue[1] = action_none;
	player.action_queue[2] = action_none;
	player.action_queue[3] = action_none;
	player.action_queue[4] = action_none;
	player.action_queue[5] = action_none;
	player.action_queue[6] = action_none;
	player.action_queue[7] = action_none;
}
