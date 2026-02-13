#pragma once

#include "../../clay.h"
#include "../ui.h"

#include <zed/app/ui.h>

void clay_tool_init() {
	clay_edit_tool_name[ clay.tool.tool_i++ ] = "CAMERA";
}

string el_table_tool_get_data( int x, int y ) {
	return "";
}

void el_table_tool_row() {
	el_start;
	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;
	clay_ui_draw_button();

	self->child_position.x += 16;
	int y = self->id_in_parent;
	float2 position = self->child_position;

	clay_ui_text( el_table_tool_get_data( 0, y ), color_clay_fg );
	self->child_position = position;

	el_finish;
}

void el_table_tool_on_ui_event( ui_event event ) {
	handle_ui_event_for_list( event, &clay.ui.data_tool );
}

void el_table_tool() {
	el_start;
	el_bind( clay.ui.data_tool, el_table_tool_on_ui_event );
	ui_element_set_table();

	for ( int i = 0; i < clay.tool.tool_i; i++ ) el_table_tool_row();

	el_finish;
}

void el_column_tool() {
	el_start;
	clay_ui_draw_fill();
	el_block;

	el_header( "TOOL" );

	el_finish;
}
