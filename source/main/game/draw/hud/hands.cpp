#include "../hud.h"

#include "../../../game/player.h"

void game_draw_hud_hands( game_player &player, game_hud &hud ) {
	game_item &item = game_player_hands_get_item( player );

	hud_rect r = hud_rect_get();
	char text[32];
	sprintf( text, "" );

	if ( player.hint == hint_z_menu ) {
		for ( int i = 0; i < player.hands.item_i; i++ ) {
			float x = r.x0 + 80 * i;
			float y = r.y1 - 20;
			game_item &item = player.hands.item[i];
			sprintf( text, item_name[ item.type.i ]    ); hud_text( text, x, y,      align_left, i == player.hands.i ? 0xffcc44 : 0xffffff );
			sprintf( text, ammo_name( item.type.ammo ) ); hud_text( text, x, y - 20, align_left, i == player.hands.i ? 0xffcc44 : 0xffffff );
		}
	}

	if ( player.hint == hint_z_menu ) return;

	// gun ammo

	if ( item.type.i != item_none ) {
		switch ( item.type.i ) {
			case item_none:
			case item_torch:
			break;

			case item_sword:
			if ( player.torso == torso_throw ) sprintf( text, "1" );
			break;

			case item_us_1917_revolver:
			sprintf( text, "%i", item.magazine.count, item.chamber );
			break;

			case item_wi_1897_shotgun:
			case item_ak_1947:
			case item_us_1919_bmg:
			int chamber = item.chamber;
			if ( chamber == chamber_spent ) chamber = 0;
			sprintf( text, "%i+%i", item.magazine.count, chamber );
			break;
		}

		if ( player_stance_is_ready( player ) ) if ( text ) hud_text( text, r.x1, r.y1 - 20, align_right );
	}

	// bag ammo

	if ( player.ammo_i != ammo_none ) {
		sprintf( text, "%4i", player.bag.ammo[ player.ammo_i ] );
		if ( player_stance_is_ready( player ) ) hud_text( text, r.x1, r.y1 - 40, align_right );
	}

	// hand

	if ( player.ammo_i != ammo_none and item.type.i != item_none ) {
		sprintf( text, item_name[ item.type.i ] );
		if ( player_stance_is_ready( player ) ) hud_text( text, r.x0, r.y1 - 20, align_left );
		sprintf( text, ammo_name( (game_ammo)player.ammo_i ) );
		if ( player_stance_is_ready( player ) ) hud_text( text, r.x0, r.y1 - 40, align_left );
	}

	// offhand

	// if ( player.hands.which or player.torso == torso_grab ) {
	// 	if ( player.hands.belt[ player.hands.k ].type.i > item_sword ) {
	// 		sprintf( text, item_name[ player.hands.belt[ player.hands.k ].type.i ] );
	// 		if ( player.stance != stance_run ) hud_text( text, r.x0, r.y1 - 80, align_left );
	// 	}
	// }
}
