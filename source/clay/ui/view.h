#pragma once

#include <zed.h>
#include <zed/app/ui.h>

#include "../../clay.h"
#include "../ui.h"

string el_table_view_get_data( int x, int y ) {
	if ( x == 0 and y < array_count( view_names ) ) return view_names[y];
	return "";
}

void el_table_view_row() {
	el_start;
	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;
	clay_ui_draw_button();
	// clay_ui_draw_fill();

	//

	self->child_position.x += 16;

	//

	int y = self->id_in_parent;

	float2 position = self->child_position;

	//

	clay_ui_text( el_table_view_get_data( 0, y ), color_clay_fg );
	self->child_position = position;

	//

	el_finish;
}

void el_table_view_on_ui_event( ui_event event ) {
	handle_ui_event_for_list( event, &clay.ui.data_view );
}

void el_table_view() {
	el_start;
	el_bind( clay.ui.data_view, el_table_view_on_ui_event );
	ui_element_set_table( 48 );

	for ( int i = 0; i < array_count( view_names ); i++ ) el_table_view_row();

	el_finish;
}

void el_column_view() {
	el_start;
	clay_ui_draw_fill();
	el_block;
	ui_element_set_padding(2);

	el_header( "VIEW" );
	el_table_view();

	switch ( clay.page_view ) {
		case clay_page_view_game:
		break;

		case clay_page_view_disk:
		break;

		case clay_page_view_size:
		break;

		case clay_page_view_perf:
		break;

		case clay_page_view_video:
		break;

		case clay_page_view_audio:
		break;

		case clay_page_view_input:
		break;
	}

	el_finish;
}
