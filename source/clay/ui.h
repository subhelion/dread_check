#pragma once

#include "../data/color.h"

#include <zed/app/graphics.h>
#include <zed/app/ui.h>

#define el_start        int id = ui_element_start();
#define el_finish       ui_element_finish( id );
#define el_block        ui_element_set_block();
#define el_size( x )    ui_element_set_height( x );
#define el_pad( x )     ui_element_set_padding( x );
#define el_pad( x, y )  ui_element_set_padding( x, y );
#define el_bind( x, y ) ui_element_bind( x, y );

void clay_ui_draw_fill( uint color = color_clay_bg ) {
	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;
	ui.data.draw_nodes[ ui.id_draw++ ] = { self->position, self->size, { 0, 0 }, color };
}

void clay_ui_draw_empty( uint color = color_clay_bg ) {
	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;
	ui.data.draw_nodes[ ui.id_draw++ ] = { self->position, self->size, { 0, 0 }, color };
}

void clay_ui_draw_border() {
	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;
	ui.data.draw_nodes[ ui.id_draw++ ] = { self->position, self->size, { 0, 0 }, color_clay_border };
}

void clay_ui_draw_button() {
	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;
	ui_element_step_node *parent = ui.data.step_nodes + self->id_parent;
	ui_element_data *parent_data   = (ui_element_data *)parent->data;

	float x = self->position.x;
	float y = self->position.y;
	float w = self->size    .x;
	float h = self->size    .y;

	uint color_el = color_clay_bg;

	if ( ui.id_hover == ui.id_current ) {
		color_el = color_clay_bg_hover;

		if ( ui.id_active == ui.id_current ) {
			color_el = color_clay_bg_active;
		}
	}

	ui.data.draw_nodes[ ui.id_draw++ ] = { { x, y }, { w, h }, { 0, 0 }, color_el };

	if ( parent_data->id_target == self->id_in_parent ) {
		ui.data.draw_nodes[ ui.id_draw++ ] = { { x, y }, { 8, h }, { 0, 0 }, color_clay_active };
	}
}

void clay_ui_text( string text, uint color ) {
	ui_element_step_node *self = ui.data.step_nodes + ui.id_current;

	// todo
	float line_height = 32;
	float padding = ( self->size.y - line_height ) / 2;
	float2 position = self->child_position;

	position.y += padding;

	app_graphics_draw_text( text, position.x, position.y, color );
}

void el_header( string text ) {
	el_start;
	el_block;
	ui_element_set_height( 96 );
	ui_element_set_padding( 16, 0 );
	clay_ui_text( text, color_clay_fg );
	ui_element_finish( id, text );
}

void el_br() {
	el_start;
	el_block;
	ui_element_set_height(2);
	clay_ui_draw_border();
	el_finish;
}

void el_border() {
	el_start;
	clay_ui_draw_border();
	el_finish;
}

void el_input_interior() {
	el_start;
	clay_ui_draw_fill();
	el_finish;
}

void el_input() {
	el_start;
	clay_ui_draw_border();
	el_block;
	ui_element_set_padding( 2 );

	el_input_interior();

	el_finish;
}

void el_address() {
	el_start; el_block; el_size( 96 ); el_pad( 16, 0 );
	el_input();
	el_finish;
}
