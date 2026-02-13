#pragma once

#include <zed/app/ui.h>

#include "../../clay.h"
#include "../ui.h"

//

void el_table_layers_on_ui_event( ui_event event ) {
	handle_ui_event_for_list( event, &clay.ui.data_layers );
}

//

string el_table_layers_get_data( int x, int y ) {
	if ( x == 0 and y == 0 ) return "Composite > Shader (basic.hlsl)";
	if ( x == 0 and y == 1 ) return "Normals";
	if ( x == 0 and y == 2 ) return "Wireframe";

	return table_buffer;
}

//

void el_table_layers_row() {
	el_start;
	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;
	clay_ui_draw_button();

	self->child_position.x += 16;
	int y = self->id_in_parent;
	float2 position = self->child_position;
	clay_ui_text( el_table_layers_get_data( 0, y ), color_clay_fg );
	self->child_position = position;
// 	self->child_position.x += 200;
//
// 	//
//
// 	clay_ui_text( el_table_layers_get_data( 1, y ), color_clay_fg );
// 	self->child_position = position;

	el_finish;
}

//

void el_table_layers() {
	el_start;
	el_bind( clay.ui.data_layers, el_table_layers_on_ui_event );
	ui_element_set_table( 48 );

	el_table_layers_row();
	el_table_layers_row();
	el_table_layers_row();

	ui_element_finish( id, "table layers" );
}

//

void el_table_inspect_on_ui_event( ui_event event ) {
	handle_ui_event_for_list( event, &clay.ui.data_inspect );
}

//

string el_table_inspect_get_data( int x, int y ) {
	#define field( type, name, semantic ) \
		if ( x == 0 and y == __LINE__ - 1 ) return #name;
	#include "../studio.inl"
	#undef field

	#define field( type, name, semantic ) \
		if ( x == 1 and y == __LINE__ - 1 ) htoh( table_buffer, vtoh( clay.edit_model.studio.name ) );
	#include "../studio.inl"
	#undef field

	return table_buffer;
}

//

void el_table_inspect_head( string text ) {
	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;
	self->child_position.x += 16;
	clay_ui_text( text, color_clay_fg );
	self->child_position.y += self->child_size.y;
}

void el_table_inspect_row() {
	el_start;
	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;
	clay_ui_draw_button();

	self->child_position.x += 16;
	int y = self->id_in_parent;
	float2 position = self->child_position;
	clay_ui_text( el_table_inspect_get_data( 0, y ), color_clay_fg );
	self->child_position = position;
	self->child_position.x += 200;
	clay_ui_text( el_table_inspect_get_data( 1, y ), color_clay_fg );
	self->child_position = position;
	self->child_position.y += self->child_size.y;

	el_finish;
}

//

void el_table_inspect() {
	el_start;
	el_bind( clay.ui.data_inspect, el_table_inspect_on_ui_event );
	ui_element_set_table( 48 );

	el_table_inspect_row();
	el_table_inspect_row();
	// el_table_inspect_head( "light[0]" );
	el_table_inspect_row();
	el_table_inspect_row();
	// el_table_inspect_head( "light[1]" );
	el_table_inspect_row();
	el_table_inspect_row();

	el_finish;
}

//

void el_palette_on_ui_event( ui_event event ) {

}

//

void el_palette() {
	el_start;
	el_bind( clay.ui.data_palette, el_palette_on_ui_event );
	el_finish;
}

//

void el_debug() {
	el_start;
	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;

	sprintf( table_buffer, "%f", clay.camera.rotation.x ); clay_ui_text( table_buffer, color_clay_fg ); self->child_position.y += self->child_size.y;
	sprintf( table_buffer, "%f", clay.camera.rotation.y ); clay_ui_text( table_buffer, color_clay_fg ); self->child_position.y += self->child_size.y;
	sprintf( table_buffer, "%f", clay.camera.rotation.z ); clay_ui_text( table_buffer, color_clay_fg ); self->child_position.y += self->child_size.y;

	el_finish;
}

//

void el_column_inspect() {
	el_start;
	clay_ui_draw_fill();
	el_block;
	ui_element_set_padding(2);

	el_header( "LAYERS" );
	el_table_layers();
	el_br();
	el_header( "INSPECT" );
	el_table_inspect();
	el_br();
	el_header( "PALETTE" );
	el_palette();
	el_br();
	el_header( "DEBUG" );
	el_debug();

	el_finish;
}
