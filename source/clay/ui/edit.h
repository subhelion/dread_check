#pragma once

#include "../../clay.h"
#include "../ui.h"

#include <zed.h>
#include <zed/app/ui.h>

string el_table_edit_get_data( int x, int y ) {
	if ( x == 0 and y < array_count( clay.edit.path ) ) {
		return clay.edit.path[y];
	}

	return "";
}

void el_table_edit_row() {
	el_start;
	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;
	clay_ui_draw_button();
	// clay_ui_draw_fill();

	self->child_position.x += 16;
	int y = self->id_in_parent;
	float2 position = self->child_position;

	clay_ui_text( el_table_edit_get_data( 0, y ), color_clay_fg );
	self->child_position = position;

	el_finish;
}

void el_table_edit_on_ui_event( ui_event event ) {
	handle_ui_event_for_list( event, &clay.ui.data_edit );

	int id = clay.ui.data_edit.id_target;
	// clay.edit_model.paths[ clay.edit_model.path ];
	clay.scene = clay_scene_edit_model;
	int c = strcmp( "data/model", clay.edit.path[ id ]  );
	printf( "%i", c );
	// if ( c == 0 )
}

void el_table_edit() {
	el_start;
	el_bind( clay.ui.data_edit, el_table_edit_on_ui_event );
	ui_element_set_table();

	for ( int i = 0; i < clay.edit.path_i; i++ ) el_table_edit_row();

	el_finish;
}

void el_column_edit() {
	el_start;
	clay_ui_draw_fill();
	el_block;
	ui_element_set_padding(2);

	el_header( "EDIT" );
	el_address();
	el_table_edit();

	el_finish;
}
