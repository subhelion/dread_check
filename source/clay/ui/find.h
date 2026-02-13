#pragma once

#include <zed/app/ui.h>

#include "../ui.h"

string find_path[64];
int find_path_i;

void clay_find_init() {
	find_path[ find_path_i++ ] = "2020 Draugb";
	find_path[ find_path_i++ ] = "2001 Halo";
	find_path[ find_path_i++ ] = "1998 Half Life";
	find_path[ find_path_i++ ] = "1996 Quake";
	find_path[ find_path_i++ ] = "1994 Marathon";
	find_path[ find_path_i++ ] = "1993 Doom";
	find_path[ find_path_i++ ] = "1992 Wolfenstein";
}

string el_table_find_get_data( int x, int y ) {
	if ( x != 0 or y >= array_count( find_path ) ) return "";
	return find_path[y];
}

void el_table_find_row() {
	el_start;
	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;
	clay_ui_draw_button();
	// draw_fill();

	self->child_position.x += 16;
	int y = self->id_in_parent;
	float2 position = self->child_position;
	clay_ui_text( el_table_find_get_data( 0, y ), color_clay_fg );
	self->child_position = position;

	el_finish;
}

void el_table_find_on_ui_event( ui_event event ) {
	handle_ui_event_for_list( event, &clay.ui.data_find );
}

void el_table_find() {
	el_start;
	el_bind( clay.ui.data_find, el_table_find_on_ui_event );
	ui_element_set_table();

	for ( int i = 0; i < find_path_i; i++ ) el_table_find_row();

	el_finish;
}

void el_column_find() {
	el_start;
	clay_ui_draw_fill();
	el_block;
	ui_element_set_padding(2);

	el_header( "FIND" );
	el_address();
	el_table_find();

	el_finish;
}
