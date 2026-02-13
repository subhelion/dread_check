#pragma once

#include <zed/app/ui.h>

#include "../../clay.h"
#include "../ui.h"

void el_menu_row( string text ) {
	el_start;
	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;
	clay_ui_draw_button();
	self->child_position.x += 16;
	self->child_position.y += 2;

	clay_ui_text( text, color_clay_fg );

	el_finish;
}

void el_menu_play() {
	el_menu_row( "PLAY" );
}

void el_menu_view() {
	el_menu_row( "VIEW" );
}

void el_menu_edit() {
	el_menu_row( "EDIT" );
}

void el_menu_find() {
	el_menu_row( "FIND" );
}

void el_menu_sync() {
	el_menu_row( "SYNC" );
}

void el_menu_itch() {
	el_menu_row( "ITCH" );
}

void el_menu_user() {
	el_menu_row( "USER" );
}

void el_menu_on_ui_event( ui_event event ) {
	handle_ui_event_for_list( event, &clay.ui.data_menu );

	if ( clay.ui.data_menu.id_preview != -1 ) {
		clay.page = (clay_page_menu)clay.ui.data_menu.id_preview;
	} else {
		clay.page = (clay_page_menu)clay.ui.data_menu.id_target;
	}
}

void el_column_menu() {
	el_start;
	el_bind( clay.ui.data_menu, el_menu_on_ui_event );
	clay_ui_draw_fill();
	ui_element_set_table( 96 );

	el_menu_play();
	el_menu_view();
	el_menu_edit();
	el_menu_find();
	el_menu_sync();
	el_menu_itch();
	el_menu_user();

	el_finish;
}
