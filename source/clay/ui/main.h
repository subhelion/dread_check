#pragma once

#include "../ui.h"

#include <zed/app/ui.h>

void edit_model_on_ui_event( ui_event );

string el_table_assets_get_data( int x, int y ) {
	if ( x == 0 and y == 0 ) return "abc";
	if ( x == 0 and y == 1 ) return "def";
	if ( x == 0 and y == 2 ) return "ghi";

	return "";
}

void el_table_assets_row() {
	el_start;
	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;
	clay_ui_draw_fill();

	self->child_position.x += 16;
	int y = self->id_in_parent;
// 	float2 position = self->child_position;
	clay_ui_text( el_table_assets_get_data( 0, y ), color_clay_fg );
// 	self->child_position = position;

	el_finish;
}

void el_table_assets() {
	el_start;
	int tabs = 8;
	int size = 560;
	int flex[] = { 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2 };
	ui_element_set_flex( flex, tabs * 2 - 1 );

	for ( int i = 0; i < tabs; i ++ ) {
		if ( i > 0 ) el_border();
		el_table_assets_row();
	}

	el_finish;
}

void el_column_main() {
	el_start;
	ui_element_step_node *self = ui.data.step_nodes + id;
	self->handle_ui_event = edit_model_on_ui_event;
	// clay_ui_draw_fill();
	el_block;

	// el_header( "MAIN" );
	// el_table_assets();

	el_finish;
}
