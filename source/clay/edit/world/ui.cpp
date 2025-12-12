#include "../../../main.h"
#include "../../../main/game.h"
#include "../world.h"

#include <zed/app/input.h>
#include <zed/xmath.h>

void pick() {
	matrix clip = game.draw.per_frame.camera.matrix_clip;

	float x = (  2.0 * ui.event.mouse.x / app.graphics.display_size.x - 1.0 ) / clip.r[0].m128_f32[0];
	float y = ( -2.0 * ui.event.mouse.y / app.graphics.display_size.y + 1.0 ) / clip.r[1].m128_f32[1];

	// todo why four components
	float4 ray_origin    = { 0, 0, 0, 1 };
	float4 ray_direction = { x, y, 1, 0 };

	matrix iv = inverse( game.draw.per_frame.camera.matrix_view );

	ray_origin    = mul( ray_origin,    iv );
	ray_direction = mul( ray_direction, iv );

	float3 plane_point  = { 0, floor_i * wall_height, 0 };
	float3 plane_normal = { 0, 1, 0 };

	// todo what size is a 'plane' vector
	xm_vector plane_ground = XMPlaneFromPointNormal( plane_point, plane_normal );

	float3 result = XMPlaneIntersectLine( plane_ground, ray_origin, ray_origin + ray_direction );

	cursor = result;
}

void tool_room_on_ui_event( ui_event event );

void clay_edit_world_on_ui_event( ui_event event ) {
	switch ( tool_i ) {
		case tool_pick: break;
		case tool_room: tool_room_on_ui_event( event ); return;
		case tool_yard: break;
		case tool_wall: break;
		case tool_tour: break;
	}

	switch ( event.type ) {
		case event_type_click: break;

		case event_type_down: {
			// todo
			// latch_reset();

			break;
		}

		case event_type_drag: {
			// todo
			// latch_test( &event );

			if ( event.type == event_type_none ) return;

			if ( event.type == event_type_down ) {
				// rotation_start_x = game.camera.rotation.x;
				// rotation_start_y = game.camera.rotation.y;

				// dx = 0;
				// dy = 0;

				return;
			}

			// dx = event.data.drag.delta.x;
			// dy = event.data.drag.delta.y;

			break;
		}

		case event_type_click2: {
			// rotation_start_x = 0;
			// rotation_start_y = 0;

			// dx = 0;
			// dy = 0;

			break;
		}

		case event_type_wheel: break;
	}
}

void clay_edit_world_ui_step() {
	// zed_show_cursor();

	// game.camera.rotation.x += midi_state.control[16] * 360.0 / 16.0;
	// game.camera.rotation.y += midi_state.control[17] * 360.0 / 16.0;
	// game.camera.rotation.z += midi_state.control[18] * 360.0 / 16.0;

	// game.camera.rotation.x = rotation_start_x + dy / 16.0;
	// game.camera.rotation.y = rotation_start_y + dx / 8.0;

	if ( false ) {
		// todo rewrite this in terms of "direction" so that diagonal movement isn't faster

		if ( ui.event.mouse.x == 0                               ) game.camera.rotation.y -= 0.5 * zed_get_screen_aspect_inline();
		if ( ui.event.mouse.x == app.graphics.display_size.x - 1 ) game.camera.rotation.y += 0.5 * zed_get_screen_aspect_inline();
		if ( ui.event.mouse.y == 0                               ) game.camera.rotation.x -= 0.5;
		if ( ui.event.mouse.y == app.graphics.display_size.y - 1 ) game.camera.rotation.x += 0.5;

		float3 move = { 0, 0, 0 };

		if ( app_input.get.key_w.held ) move += zed_camera_walk( game.camera,  0,  1, 0 );
		if ( app_input.get.key_a.held ) move += zed_camera_walk( game.camera, -1,  0, 0 );
		if ( app_input.get.key_s.held ) move += zed_camera_walk( game.camera,  0, -1, 0 );
		if ( app_input.get.key_d.held ) move += zed_camera_walk( game.camera,  1,  0, 0 );

		float speed = 0.05;

		if ( app_input.get.key_shift.held ) speed = 0.2;

		game.camera.position.x += move.x * speed;
		game.camera.position.y += move.y * speed;
		game.camera.position.z += move.z * speed;
	}

	//

	float3 move = { 0, 0, 0 };

	if ( ui.event.mouse.x == 0                               ) move += zed_camera_walk( game.camera, -1,  0, 0 );
	if ( ui.event.mouse.x == app.graphics.display_size.x - 1 ) move += zed_camera_walk( game.camera,  1,  0, 0 );
	if ( ui.event.mouse.y == 0                               ) move += zed_camera_walk( game.camera,  0,  1, 0 );
	if ( ui.event.mouse.y == app.graphics.display_size.y - 1 ) move += zed_camera_walk( game.camera,  0, -1, 0 );

	float speed = 0.05;

	game.camera.position.x += move.x * speed;
	game.camera.position.y += move.y * speed;
	game.camera.position.z += move.z * speed;

	//

	if ( app_input.get.key_1.fall ) tool_i = 1;
	if ( app_input.get.key_2.fall ) tool_i = 2;
	if ( app_input.get.key_3.fall ) tool_i = 3;
	if ( app_input.get.key_4.fall ) tool_i = 4;
	if ( app_input.get.key_5.fall ) tool_i = 5;

	//

	if ( app_input.get.key_prior.fall ) floor_i += 1;
	if ( app_input.get.key_next .fall ) floor_i -= 1;

	//

	cursor = { 0, 0, 0 };

	// todo
	zed_camera_update( game.camera, &game.draw.camera );

	pick();
}
