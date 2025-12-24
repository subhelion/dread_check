#include "../../../data/color.h"
#include "../../../data/gfx.h"
#include "../../canvas.h"
#include "../../game.h"
#include "../../game/roster.h"

#include <zed/app/graphics.h>

#include "../menu.h"

#include <zed.h>
#include <zed/app/ui.h>

#include "action.h"
#include "draw.h"
#include "sfx.h"

bool check_hover( int x, int y, int w, int h ) {
	int mx = floor( ui.event.mouse.x * canvas_x1.size.y / app.system.device_size.y );
	int my = floor( ui.event.mouse.y * canvas_x1.size.y / app.system.device_size.y );

	return mx > x and my > y and mx < x + w and my < y + h;
}

//

typedef void (*game_menu_cb_t)( game_menu &menu );
#define game_menu_cb []( game_menu &menu )

void game_menu_label( game_menu &menu, string text, float x, float y ) {
	if ( menu.signal == game_menu_signal_render ) app_graphics_draw_text_new( text, x, y, color_menu_fg );
}

void game_menu_item( game_menu &menu, string text, float x, float y, game_menu_cb_t action = {} ) {
	int id = menu.j ++;

	if ( menu.signal == game_menu_signal_render ) app_graphics_draw_text_new( text, x, y, menu.state.x == 0 and menu.state.y == id ? color_menu_fg_active : color_menu_fg );
	if ( menu.signal == game_menu_signal_hover ) if ( check_hover( x, y, app_graphics_text_measure( text ), 20 ) ) { menu.state.x = 0; menu.state.y = id; }
	if ( menu.signal == game_menu_signal_select and action and menu.state.x == 0 and menu.state.y == id ) action( menu );
}

void game_menu_item_int( game_menu &menu, string text, float x, float y, game_menu_cb_t action_left, game_menu_cb_t action_right ) {
	int id = menu.j ++;
	if ( menu.signal == game_menu_signal_render ) app_graphics_draw_text_new( text, x, y, menu.state.x == 0 and menu.state.y == id ? color_menu_fg_active : color_menu_fg );
	if ( menu.signal == game_menu_signal_hover ) if (  check_hover( x, y, app_graphics_text_measure( text ), 20 ) ) { menu.state.x = 0; menu.state.y = id; }
	if ( menu.signal == game_menu_signal_left  and action_left  and menu.state.x == 0 and menu.state.y == id ) action_left ( menu );
	if ( menu.signal == game_menu_signal_right and action_right and menu.state.x == 0 and menu.state.y == id ) action_right( menu );
}

void game_menu_item_back( game_menu &menu, float x, float y ) {
	game_menu_item( menu, "Back", x, y, game_menu_cb { game_menu_action_back( menu ); });
}

void game_menu_item_status( game_menu &menu, float x, float y ) {
	// game_menu_item( menu, menu_status_offline ? "Status: Offline" : "Status: Online", x, y, game_menu_cb { toggle_status(); });

	if ( true ) {
		game_menu_label( menu, "Gamepad detected", x, y );
	} else {
		game_menu_label( menu, "Gamepad recommended", x, y );
	}
}

void game_menu_item_face( game_menu &menu, float x, float y, game_menu_cb_t action = {} ) {
	y += 4;

	int id = menu.j ++;

	int w = 64;
	int h = 64;

	if ( menu.signal == game_menu_signal_render ) {
		zed_pass_reset( pass_title );

		zed_draw_image( gfx_face[ roster[ i_static_temp ].face_i ], x + 64 * 0, y );

		if ( menu.state.x == 0 and menu.state.y == id ) {
			zed_draw_rect_empty( x, y, w, h, menu.state.x == 0 and menu.state.y == id ? color_menu_fg_active : color_menu_fg, 2 );
		}
	}

	if ( menu.signal == game_menu_signal_hover ) if ( check_hover( x, y, w, h ) ) { menu.state.x = 0; menu.state.y = id; menu_roster_hover = true; menu_roster_hover_i = i_static_temp; }
	if ( menu.signal == game_menu_signal_select and action and menu.state.x == 0 and menu.state.y == id ) action( menu );
}

void game_menu_item_squad( game_menu &menu, float x, float y ) {
	y += 4;

	int id = menu.j ++;

	int w = 64 * local_player_count;
	int h = 64;

	if ( menu.signal == game_menu_signal_render ) {
		zed_pass_reset( pass_title );

		if ( local_player_count >= 1 ) zed_draw_image( gfx_face[ roster[ menu_character_0_i ].face_i ], x + 64 * 0, y );
		if ( local_player_count >= 2 ) zed_draw_image( gfx_face[ roster[ menu_character_1_i ].face_i ], x + 64 * 1, y );
		if ( local_player_count >= 3 ) zed_draw_image( gfx_face[ roster[ menu_character_2_i ].face_i ], x + 64 * 2, y );
		if ( local_player_count == 4 ) zed_draw_image( gfx_face[ roster[ menu_character_3_i ].face_i ], x + 64 * 3, y );

		if ( menu.state.x == 0 and menu.state.y == id ) {
			zed_draw_rect_empty( x, y, w, h, menu.state.x == 0 and menu.state.y == id ? color_menu_fg_active : color_menu_fg, 2 );
		}
	}

	if ( menu.signal == game_menu_signal_hover  ) if ( check_hover( x, y, w, h ) ) { menu.state.x = 0; menu.state.y = id; }

	game_menu_cb_t action = game_menu_cb { game_menu_push( menu, game_menu_page_roster ); menu_roster_page = 0; game_roster_init( menu_roster_page ); };

	if ( menu.signal == game_menu_signal_select and action and menu.state.x == 0 and menu.state.y == id ) action( menu );
}

void game_menu_item_pc( game_menu &menu, float x, float y, float w, float h, game_menu_cb_t action = {} ) {
	y += 4;

	int id = menu.j ++;

	if ( menu.signal == game_menu_signal_render ) {
		zed_pass_reset( pass_title );

		if ( menu.state.x == 0 and menu.state.y == id ) {
			zed_draw_rect_empty( x, y, w, h, menu.state.x == 0 and menu.state.y == id ? color_menu_fg_active : color_menu_fg, 2 );
		}
	}

	if ( menu.signal == game_menu_signal_hover ) if ( check_hover( x, y, w, h ) ) { menu.state.x = 0; menu.state.y = id; }
	if ( menu.signal == game_menu_signal_select and action and menu.state.x == 0 and menu.state.y == id ) action( menu );
}

void game_menu_main_begin( game_menu &menu ) {
	menu.j = 0;
	menu_did_back = false;
}

void game_menu_main( game_menu &menu, game_menu_signal signal ) {
	if ( not menu.state.page ) return;

	menu.signal = signal;

	float x = ( (float)canvas_x1.size.x - 320 ) / 2 + 10;
	float y = (float)canvas_x1.size.y / 2;

	if ( split == game_split_duo ) {
		x = 0;
	}

	game_menu_main_begin( menu );

	switch ( menu.state.page ) {
		case game_menu_page_start: {
			game_menu_item( menu, "Play",     x, y +  0, game_menu_cb { game_menu_push( menu, game_menu_page_play    ); });
			game_menu_item( menu, "Options",  x, y + 20, game_menu_cb { game_menu_push( menu, game_menu_page_options ); });
			game_menu_item( menu, "Credits",  x, y + 40, game_menu_cb { game_menu_push( menu, game_menu_page_credits ); });
			game_menu_item( menu, "Exit",     x, y + 60, game_menu_cb { app_exit();                                     });
			game_menu_item( menu, "Continue", x, y - 70, game_menu_cb { game_menu_action_start_game_1p( menu );         });

			float x = 37;
			float y = 10;
			float w = 150; // 200; // 100; // 40;
			float h = 120; // 160; //  80; // 32;

			game_menu_item_pc( menu, (float)canvas_x1.size.x / 2 - w / 2 + x, (float)canvas_x1.size.y / 2 - h / 2 + 12 + y, w, h, game_menu_cb {
				game_menu_push( menu, game_menu_page_maze );
				game.scene = scene_maze;
				maze_init();
				maze_start();
			});

			break;
		}

		case game_menu_page_maze: {
			game_menu_item( menu, "START 1P", 216, 146, game_menu_cb { game_menu_action_start_maze_1p( menu ); });
			game_menu_item( menu, "START 2P", 216, 166, game_menu_cb { game_menu_action_start_maze_2p( menu ); });
			game_menu_item_back( menu, x + 8, 4 );

			break;
		}

		case game_menu_page_play: {
			game_menu_item( menu, "1 Player", x, y +   0, game_menu_cb { local_player_count =  1; game_menu_push( menu, game_menu_page_play_mode ); });
			game_menu_item( menu, "2 Player", x, y +  20, game_menu_cb { local_player_count =  2; game_menu_push( menu, game_menu_page_play_mode ); });
			game_menu_item( menu, "3 Player", x, y +  40, game_menu_cb { local_player_count =  3; game_menu_push( menu, game_menu_page_play_mode ); });
			game_menu_item( menu, "4 Player", x, y +  60, game_menu_cb { local_player_count =  4; game_menu_push( menu, game_menu_page_play_mode ); });

			game_menu_item_back  ( menu, x,  0 );
			game_menu_item_status( menu, x, 20 );

			break;
		}

		case game_menu_page_play_mode: {
			game_menu_item( menu, "Action",    x, y +  0, game_menu_cb { game_menu_push( menu, game_menu_page_play_action    ); });
			game_menu_item( menu, "Adventure", x, y + 20, game_menu_cb { game_menu_push( menu, game_menu_page_play_adventure ); });

			game_menu_item( menu, "Peaceful",  x, y + 60 );
			game_menu_item( menu, "Creative",  x, y + 80 );

			game_menu_item_back  ( menu, x,  0 );
			game_menu_item_status( menu, x, 20 );
			game_menu_item_squad ( menu, x, 40 );

			break;
		}

		case game_menu_page_play_action: {
			game_menu_item( menu, "Alfa",    x, y +   0, game_menu_cb { game_menu_push( menu, game_menu_page_play_action_channel ); });
			game_menu_item( menu, "Bravo",   x, y +  20, game_menu_cb { game_menu_push( menu, game_menu_page_play_action_channel ); });
			game_menu_item( menu, "Charlie", x, y +  40, game_menu_cb { game_menu_push( menu, game_menu_page_play_action_channel ); });
			game_menu_item( menu, "Delta",   x, y +  60, game_menu_cb { game_menu_push( menu, game_menu_page_play_action_channel ); });
			game_menu_item( menu, "Echo",    x, y +  80, game_menu_cb { game_menu_push( menu, game_menu_page_play_action_channel ); });
			game_menu_item( menu, "Foxtrot", x, y + 100, game_menu_cb { game_menu_push( menu, game_menu_page_play_action_channel ); });

			game_menu_item_back  ( menu, x,  0 );
			game_menu_item_status( menu, x, 20 );
			game_menu_item_squad ( menu, x, 40 );

			break;
		}

		case game_menu_page_play_action_channel: {
			game_menu_game_start( menu );

			break;
		}

		case game_menu_page_play_adventure: {
		    game_menu_item( menu, "Find Game(Online)", x, y +  0 );
			game_menu_item( menu, "Load Game", x, y + 20, game_menu_cb { game_menu_push( menu, game_menu_page_play_adventure_load ); });
			game_menu_item( menu, "New Game",  x, y + 40, game_menu_cb { game_menu_push( menu, game_menu_page_play_adventure_new  ); });

			game_menu_item_back  ( menu, x,  0 );
			game_menu_item_status( menu, x, 20 );
			game_menu_item_squad ( menu, x, 40 );

			break;
		}

		case game_menu_page_play_adventure_load: {
			game_menu_item( menu, "Empty",   x, y +   0 );
			game_menu_item( menu, "Empty",   x, y +  20 );
			game_menu_item( menu, "Empty",   x, y +  40 );
			game_menu_item( menu, "Empty",   x, y +  60 );
			game_menu_item( menu, "Empty",   x, y +  80 );
			game_menu_item( menu, "Empty",   x, y + 100 );

			game_menu_item_back  ( menu, x,  0 );
			game_menu_item_status( menu, x, 20 );
			game_menu_item_squad ( menu, x, 40 );

			break;
		}

		case game_menu_page_play_adventure_new: {
			char text_chapter [32];

			// if ( menu_campaign_i == 0 ) {
				// sprintf( text_chapter, "Chapter: %s-%s", name_campaign[ menu_campaign_i ], name_chapter[ menu_chapter_i ] );
			// } else {
				sprintf( text_chapter, "Chapter: %s", name_campaign[ menu_campaign_i ] );
			// }

			char text_privacy[32]; sprintf( text_privacy, "Privacy: %s", name_privacy [ menu_privacy_i  ] );
			char text_chat   [32]; sprintf( text_chat,    "Chat: %s",    name_chat    [ menu_chat_i     ] );
			char text_rules  [32]; sprintf( text_rules,   "Rules: %s", "Default" );
			char text_cheats [32]; sprintf( text_cheats,  "Cheats: %i", 0 );


			game_menu_item( menu, text_chapter,  x, y +   0, game_menu_cb { game_menu_push( menu, game_menu_page_play_adventure_campaign );        });
			game_menu_item( menu, text_privacy,  x, y +  20, game_menu_cb { menu_privacy_i = ( menu_privacy_i + 1 ) % array_count( name_privacy ); });
			// game_menu_item( menu, text_chat,     x, y +  40, game_menu_cb { menu_chat_i    = ( menu_chat_i    + 1 ) % array_count( name_chat    ); });
			// game_menu_item( menu, text_rules,    x, y +  60, game_menu_cb {}                                                                         );
			// game_menu_item( menu, text_cheats,   x, y +  80, game_menu_cb {}                                                                         );
			game_menu_item( menu, "Launch Game", x, y + 100, game_menu_cb {                                                                        });

			game_menu_item_back  ( menu, x,  0 );
			game_menu_item_status( menu, x, 20 );
			game_menu_item_squad ( menu, x, 40 );

			break;
		}

		case game_menu_page_play_adventure_campaign: {


			for ( int i = 0; i < array_count( name_campaign ); i++ ) {
				i_static_temp = i;
				char text_campaign[32]; sprintf( text_campaign, "%s %s", date_campaign[ i ], name_campaign[ i ] );

				game_menu_item( menu, text_campaign, x, 40 + 20 * i, game_menu_cb {
					menu_campaign_i = i_static_temp;
					// menu_chapter_i = 0;
					// if ( i_static_temp == 0 ) {
						// game_menu_push( menu, game_menu_page_play_adventure_chapter );
					// } else {
						game_menu_pop( menu );
					// }
				});
			}

			game_menu_item_back( menu, x,  0 );

			game_menu_item( menu, "Date", x, 20 );

			break;
		}

		case game_menu_page_play_adventure_chapter: {
			if ( menu_campaign_i == 0 ) {
				for ( int i = 0; i < array_count( name_chapter ); i++ ) {
					i_static_temp = i;
					char text[32]; sprintf( text, "%s", name_chapter[ i ] );
					game_menu_item( menu, text, x, y + 20 * i, game_menu_cb { menu_campaign_i = i_static_temp; game_menu_pop( menu ); game_menu_pop( menu ); });
				}
			} else {

			}

			game_menu_item_back  ( menu, x,  0 );
			game_menu_item_status( menu, x, 20 );
			game_menu_item_squad ( menu, x, 40 );

			break;
		}

		case game_menu_page_roster: {
			if ( signal == game_menu_signal_hover ) menu_roster_hover = false;
			y = 40;

			for ( int i = 0; i < 15; i ++ ) {
				int dx = i % 5;
				int dy = ( i - dx ) / 5;
				i_static_temp = i;

				game_menu_item_face( menu, x + dx * 64, y + dy * 64, game_menu_cb {
					menu_character_0_i = i_static_temp;
					// game_menu_pop( menu );
					game_menu_push( menu, game_menu_page_roster_character );
				});
			}

			game_menu_item_back( menu, x,  0 );
			char *fields[] = { "Name", "Height", "Weight", "Primary", "Secondary", "Equipment", "Cash" };

			char *field_primary  [] = { "Rifle", "Rifle", "Rifle", "Rifle", "Shotgun", "SMG", "SMG", "HMG" };
			char *field_secondary[] = { "Pistol", "Pistol", "Pistol", "Revolver", "Revolver", "SMG", "Shotgun", "Grenades" };
			char *field_equipment[] = { "Medical", "Electrical", "Structural", "Tactical", "None", "None", "None", "None" };

			// medical:
			// electrical:
			// structural: hammer, axe, ladder
			// tactical:
			// everyone: flashlight, knife, radio

			if ( menu_roster_hover ) {
				char *text;

				char temp[32];

				switch( menu_roster_field_i ) {
					case 0: text = names[ roster[ menu_roster_hover_i ].name_i ];                 break;
					case 1: sprintf( temp, "%i cm", roster[ menu_roster_hover_i ].height    ); text = temp; break;
					case 2: sprintf( temp, "%i kg", roster[ menu_roster_hover_i ].weight    ); text = temp; break;
					case 3: text = field_primary  [ roster[ menu_roster_hover_i ].primary   ]; break;
					case 4: text = field_secondary[ roster[ menu_roster_hover_i ].secondary ]; break;
					case 5: text = field_equipment[ roster[ menu_roster_hover_i ].equipment ]; break;
					case 6: sprintf( temp, "$%i",   roster[ menu_roster_hover_i ].cash      ); text = temp; break;
				}

				game_menu_label( menu, text, x, 20 );
			} else {
				game_menu_item( menu, fields[ menu_roster_field_i ], x, 20, game_menu_cb { menu_roster_field_i = ( menu_roster_field_i + 1 ) % array_count( fields ); });
			}

			game_menu_item( menu, "Recruit", x + 320 - app_graphics_text_measure( "Recruit" ), 20, game_menu_cb { game_menu_roster_recruit(); });

			break;
		}

		case game_menu_page_roster_character: {
			game_menu_item( menu, "Confirm", x, y + 100, game_menu_cb { game_menu_pop( menu ); game_menu_pop( menu ); });

			game_menu_item_back( menu, x, 0 );
			game_menu_item( menu, "Prev", x,                                             200, game_menu_cb { menu_character_0_i = ( menu_character_0_i - 1 + 15 ) % 15; });
			game_menu_item( menu, "Next", x + 320 - app_graphics_text_measure( "Next" ), 200, game_menu_cb { menu_character_0_i = ( menu_character_0_i + 1 + 15 ) % 15; });

			char *fields[] = { "Name", "Height", "Weight", "Primary", "Secondary", "Equipment", "Cash" };

			char *field_primary  [] = { "Rifle", "Rifle", "Rifle", "Rifle", "Shotgun", "SMG", "SMG", "HMG" };
			char *field_secondary[] = { "Pistol", "Pistol", "Pistol", "Revolver", "Revolver", "SMG", "Shotgun", "Grenades" };
			char *field_equipment[] = { "Medical", "Electrical", "Structural", "Tactical", "None", "None", "None", "None" };

			game_menu_label( menu, names[ roster[ menu_character_0_i ].name_i    ], x, 20 );

			y = 40;

			i_static_temp = menu_character_0_i;
			game_menu_item_face( menu, x, y );

			char temp[32];

			sprintf( temp, "%3i yo", roster[ menu_character_0_i ].age    ); game_menu_label( menu, temp, x + 70, y      );
			sprintf( temp, "%3i cm", roster[ menu_character_0_i ].height ); game_menu_label( menu, temp, x + 70, y + 20 );
			sprintf( temp, "%3i kg", roster[ menu_character_0_i ].weight ); game_menu_label( menu, temp, x + 70, y + 40 );

			game_menu_label( menu, field_primary  [ roster[ menu_character_0_i ].primary   ], x, y +  80 );
			game_menu_label( menu, field_secondary[ roster[ menu_character_0_i ].secondary ], x, y + 100 );
			game_menu_label( menu, field_equipment[ roster[ menu_character_0_i ].equipment ], x, y + 120 );

			sprintf( temp, "$%i", roster[ menu_character_0_i ].cash );
			game_menu_label( menu, temp, x, y + 140 );

			break;

		}

		case game_menu_page_options: {
			game_menu_item( menu, "Input", x, y +  0, game_menu_cb { game_menu_push( menu, game_menu_page_options_input ); });
			game_menu_item( menu, "Video", x, y + 20, game_menu_cb { game_menu_push( menu, game_menu_page_options_video ); });
			game_menu_item( menu, "Audio", x, y + 40, game_menu_cb { game_menu_push( menu, game_menu_page_options_audio ); });
			game_menu_item( menu, "Data",  x, y + 60, game_menu_cb { game_menu_push( menu, game_menu_page_options_data  ); });

			game_menu_item_back( menu, x,  0 );

			break;
		}

		case game_menu_page_options_input: {
			game_menu_item( menu, "Singleplayer", x, y +  0, game_menu_cb { game_menu_push( menu, game_menu_page_options_input_singleplayer ); });
			game_menu_item( menu, "Multiplayer",  x, y + 20, game_menu_cb { game_menu_push( menu, game_menu_page_options_input_multiplayer  ); });

			game_menu_item_back( menu, x,  0 );

			break;
		}
		case game_menu_page_options_input_singleplayer: {
			game_menu_item_back( menu, x,  0 );

			break;
		}

		case game_menu_page_options_input_multiplayer: {
			game_menu_item( menu, "P1:Keyboard",  x, y +  0 );
			game_menu_item( menu, "P2:Gamepad 1", x, y + 20 );
			game_menu_item( menu, "P3:Gamepad 2", x, y + 40 );
			game_menu_item( menu, "P4:Gamepad 3", x, y + 60 );

			game_menu_item_back( menu, x,  0 );

			break;
		}

		case game_menu_page_options_video: {
			char canvas_size_x[32]; sprintf( canvas_size_x, "Canvas X:%i", canvas_x1.size.x );
			char canvas_size_y[32]; sprintf( canvas_size_y, "Canvas Y:%i", canvas_x1.size.y );
			char device_size_x[32]; sprintf( device_size_x, "Device X:%i", app.system.device_size.x );
			char device_size_y[32]; sprintf( device_size_y, "Device Y:%i", app.system.device_size.y );

			game_menu_item    ( menu, "Rotate Display", x, y +  0 );
			game_menu_item    ( menu, canvas_size_x,    x, y + 20 );
			game_menu_item    ( menu, canvas_size_y,    x, y + 40 );
			game_menu_item_int( menu, device_size_x,    x, y + 60, game_menu_cb { app.system.device_size.x -= 1; menu_sfx_dec(); }, game_menu_cb { app.system.device_size.x += 1; menu_sfx_inc(); });
			game_menu_item_int( menu, device_size_y,    x, y + 80, game_menu_cb { app.system.device_size.y -= 1; menu_sfx_dec(); }, game_menu_cb { app.system.device_size.y += 1; menu_sfx_inc(); });

			game_menu_item_back( menu, x,  0 );

			break;
		}

		case game_menu_page_options_audio: {
			game_menu_item( menu, game.is_muted ? "Unmute" : "Mute", x, y +  0, game_menu_cb { game.is_muted = not game.is_muted; });

			game_menu_item_back( menu, x,  0 );

			break;
		}

		case game_menu_page_options_data: {
			char text[32];

			sprintf( text, "User: %s",   app .user ); game_menu_label( menu, text, x, y +  0 );
			sprintf( text, "Itch: %s",   itch.user ); game_menu_label( menu, text, x, y + 20 );
			sprintf( text, "Seed: %08X", game.seed ); game_menu_label( menu, text, x, y + 40 );

			game_menu_item_back( menu, x,  0 );

			break;
		}

		case game_menu_page_credits: {
			string credits[] = {
				"DRAUGB",
				"",
				"Zachary Alexander",
				"belimoth",
				"Code, Design, Direction",
				"",
				"Ray \"Blambo\" Chen",
				"Code",
				"",
				"",

				"TESTING",
				"",
				"Andie Nare",
				"Aubrey Serr",
				"Derek Sneed",
				"James Murff",
				"Joseph Silverman",
				"Peter Queckenstedt",
				"",
				"",

				// "CHARACTER MODELS",
				// "",
				// "I've been kitbashing",
				// "these from things I",
				// "download and then",
				// "remeshing and then",
				// "decimating sorry I",
				// "didn't keep track",
				// "todo",
				// "",

				"ASSETS",
				"",
				"Richard Whitelock",
				"AllSky",
				"",
				"lodgeb84",
				"Low Poly Weapon Pack",
				"",
				"",
				"",

				"FONTS",
				"",
				"Ivano",
				"somepx",
				"Bacteria",
				"",
				"",
				"",
				"",
				"",

				"AUDIO",
				"",
				"Thievery",
				"Fraud",
				"Etc",
				"",
				"",
				"",
				"",
				"",
			};

			y = 20;

			for ( int i = 0; i < 10; i++ ) {
				game_menu_label( menu, credits[ i + ( credits_page_i * 10 ) % array_count( credits ) ], x, y + 20 * i );
			}

			game_menu_item( menu, "Next", x + 320 - app_graphics_text_measure( "Next" ), 220, game_menu_cb { credits_page_i++; });
			game_menu_item_back( menu, x, 0 );
			game_menu_item( menu, "Prev", x, 220, game_menu_cb { credits_page_i = ( credits_page_i - 1 + 10 ) % 10; });

			break;
		}

		case game_menu_page_pause: {
			string pause = game.is_paused ? "Unpause" : "Pause";
			game_menu_item( menu, "Resume",  x, y +  0, game_menu_cb { game_menu_resume( menu ); });
			game_menu_item( menu, "Options", x, y + 20, game_menu_cb { game_menu_push( menu, game_menu_page_options ); });
			game_menu_item( menu, "Credits", x, y + 40, game_menu_cb { game_menu_push( menu, game_menu_page_credits ); });
			game_menu_item( menu, "Exit",    x, y + 60, game_menu_cb { /* todo */ void game_start(); game_start();     });
			game_menu_item( menu, "Respawn", x, y - 90, game_menu_cb { game_menu_respawn( menu ); });
			game_menu_item( menu, pause,     x, y - 70, game_menu_cb { game.is_paused = ! game.is_paused; menu_did_back = true; if ( game.is_paused ) menu_sfx_start(); else menu_sfx_start(); });

			break;
		}
	}

	[&](){
		if ( menu_did_back ) return;
		if ( menu.state.x == -1 and menu.state.y == -1 and not menu.state.page == menu.state_previous.page ) return;
		if ( signal == game_menu_signal_select ) menu_sfx_enter();
		if ( menu.state.x == -1 or menu.state.y == -1 ) return;
		if ( menu.state.x == menu.state_previous.x and menu.state.y == menu.state_previous.y ) return;
		if ( signal == game_menu_signal_hover  ) menu_sfx_hover();
	}();

	if ( signal == game_menu_signal_hover ) menu.state_previous = menu.state;
}
