#include <zed/app.h>
#include <zed/app/graphics.h>

#include "canvas.h"
#include "game.h"
#include "game/draw.h"

zed_pass pass_canvas;

void game_canvas_size() {
	// int resolution =  30;
	// int resolution =  60;
	// int resolution = 120;
	int resolution = 240;
	// int resolution = 480;
	// int resolution = 960;
	// int resolution = 1980;
	// int resolution = 2160;

	int ratio  = floor( app.graphics.display_size.y / resolution );
	int width  = floor( app.graphics.display_size.x / ratio      );
	int height = floor( app.graphics.display_size.y / ratio      );

	int target_width  = width  * ratio;
	int target_height = height * ratio;

	canvas_size = { width, height };
}

void game_canvas_init() {
	game_canvas_size();

	zed_canvas_new( canvas_x1, canvas_size.x,     canvas_size.y     );
	zed_canvas_new( canvas_x2, canvas_size.x * 2, canvas_size.y * 2 );
	zed_pass_new( pass_canvas, "data/shader/zed/canvas.hlsl" );
}

//

void _canvas_set_viewport() {
	float x = ( app.graphics.display_size.x - app.graphics.render_target.size.x ) / 2;
	float y = ( app.graphics.display_size.y - app.graphics.render_target.size.y ) / 2;
	float w = app.graphics.render_target.size.x;
	float h = app.graphics.render_target.size.y;

	zed_set_viewport( x, y, w, h );
}

void game_canvas_set_split_view( int i ) {
	app_render_target target;

	target = canvas_x1.render_target;

	float x = 0;
	float y = 0;
	float w = target.size.x;
	float h = target.size.y;

	if ( split == game_split_solo ) return;
	if ( split == game_split_duo  ) w = target.size.x / 2;

	x = x + w * ( i % 2 );
	y = y + h * ( i - i % 2 ) / 2;

	zed_set_viewport( x, y, w, h );
}

void game_canvas_set_split_view_native( int i ) {
	app_render_target target;

	target = app.graphics.render_target;

	float x = 0;
	float y = 0;
	float w = target.size.x;
	float h = target.size.y;

	x = x + w * ( i % 2 );
	y = y + h * ( i - i % 2 ) / 2;

	zed_set_viewport( x, y, w, h );
}

void game_canvas_draw_for_camera_native( int i ) {
	game_canvas_set_split_view_native(i);
	game.camera = game.data.camera[i];
	zed_camera_update( game.camera, &game.draw.camera );
	game_draw_per_frame_update();
}

void game_canvas_draw_per_camera_native( void(*f)() ) {
	if ( split == game_split_solo ) {
		f();
	} else if ( split == game_split_duo ) {
		for ( int i = 0; i < 2; i++ ) {
			game_canvas_draw_for_camera_native( i );
			f();
		}
	} else if ( split == game_split_trio ) {
		for ( int i = 0; i < 3; i++ ) {
			game_canvas_draw_for_camera_native( i );
			f();
		}
	} else if ( split == game_split_quad ) {
		for ( int i = 0; i < 4; i++ ) {
			game_canvas_draw_for_camera_native( i );
			f();
		}
	}
}

//

void game_canvas_before() {
	if ( canvas_to_size ) game_canvas_size();

	zed_canvas canvas = canvas_x1;
	if ( split == game_split_duo  ) canvas = canvas_x1;
	if ( split == game_split_trio ) canvas = canvas_x2;
	if ( split == game_split_quad ) canvas = canvas_x2;

	zed_set_render_target( canvas.render_target );
	zed_canvas_clear( canvas );

	zed_camera_update( game.camera, &game.draw.camera );
	game_draw_per_frame_update();
}

void game_canvas_after() {
	zed_canvas canvas = canvas_x1;
	if ( split == game_split_duo  ) canvas = canvas_x1;
	if ( split == game_split_trio ) canvas = canvas_x2;
	if ( split == game_split_quad ) canvas = canvas_x2;

	zed_set_render_target( app.graphics.render_target );
	zed_pass_reset( pass_canvas );
	_canvas_set_viewport();
	zed_use_canvas_3d( canvas );
	zed_mesh_draw_primitive( zed_primitive_triangle_list, 3 );
}

float zed_get_screen_aspect_inline() {
	if ( split == game_split_duo ) return (float)app.graphics.render_target.size.x / 2 / (float)app.graphics.render_target.size.y;
	return (float)app.graphics.render_target.size.x / (float)app.graphics.render_target.size.y;
}
