#include "../hud.h"

#include "../../../game.h"
#include "../../../game/player.h"

void game_draw_hud_x( game_player &player, game_hud &hud ) {
	uint color = 0xffffff;
	if ( player.pad.w or player.pad.e or player.pad.n or player.pad.s or player.x_menu_handled ) color = 0xffffff; else color = 0xffcc44;
	game_item &item = game_player_hands_get_item( player );

	hud.text_w = "--";
	hud.text_e = "--";
	hud.text_n = "--"; if ( game_item_can( item, action_reload ) ) hud.text_n = "LOAD";
	hud.text_s = "--"; if ( game_item_can( item, action_unload ) ) hud.text_s = "UNLOAD";

	switch ( item.type.i ) {
		case item_none:
		case item_torch:
		case item_sword:
		case item_us_1917_revolver:
		break;

		case item_wi_1897_shotgun:
		hud.text_e = ammo_name( (game_ammo)player.ammo_i );
		hud.text_w = "AMMO";
		break;

		case item_ak_1947:
		hud.text_e = ammo_name( (game_ammo)player.ammo_i );
		hud.text_w = "MAG";
		break;

		case item_us_1919_bmg:
		hud.text_e = ammo_name( (game_ammo)player.ammo_i );
		hud.text_w = "--";
		break;
	}

	if ( player.torso == torso_none ) hud.text_w = hud.text_e = hud.text_n = hud.text_s = "--";

	hud_text( hud.text,   hud.x, hud.y,      align_center, color );
	hud_text( hud.text_n, hud.x, hud.y - 20, align_center, player.pad.n ? 0xffbb22 : 0xffffff );
	hud_text( hud.text_s, hud.x, hud.y + 20, align_center, player.pad.s ? 0xffbb22 : 0xffffff );
}
