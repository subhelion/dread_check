#pragma once

#include "../../clay.h"
#include "../../clay/studio.h"

#include <zed/app/graphics.h>

void clay_gfx_init() {
	// mesh view

	zed_pass_new( clay.gfx.pass_plane, "data/shader/clay/ui_cutting_plane.hlsl" );
	clay.gfx.pass_plane.rs = rasterizer_states.cull_none;
	zed_mesh_new_plane( clay.gfx.mesh_plane, 6, 6 );

	zed_pass_new( clay.gfx.pass_composite, "data/shader/clay/basic.hlsl"        );
	zed_pass_new( clay.gfx.pass_normals,   "data/shader/clay/debug_normal.hlsl" );
	zed_pass_new( clay.gfx.pass_wireframe, "data/shader/clay/basic.hlsl"        );

	clay.gfx.pass_wireframe.rs = rasterizer_states.wireframe;

	// zed_mesh_new( clay.edit_model.mesh, clay.edit_model.paths[ clay.edit_model.path ] );

	game.camera.position.y = 1.0;
	clay.edit_model.cursor_start = game.camera.position;
	game.camera.rotation.y = 180;
	clay.edit_model.rotation_start_x = game.camera.rotation.x;
	clay.edit_model.rotation_start_y = game.camera.rotation.y;
	clay.edit_model.camera_zoom = 3.0;

	// studio_init();

	zed_pass_new( clay.gfx.pass_grid, "data/shader/clay/grid.hlsl" );
	clay.gfx.pass_grid.rs = rasterizer_states.wireframe;
	zed_mesh_new_plane( clay.gfx.mesh_grid, 17, 17 );
}
