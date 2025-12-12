#include <zed/app.h>
#include <zed/app/system.h>
#include <zed/app/graphics.h>
#include <zed/xmath.h>
#include <zed/platform/d3d11.h>

void zed_mesh_new_from_buffer( zed_mesh &mesh, zed_data_in ) {
	zed_buffer buffer;
	zed_buffer_new_vertex( buffer, zed_data_thru );

	mesh.buffer_vertex = buffer.native;
	mesh.buffer_index  = 0;
	mesh.count_vertex  = buffer.count;
	mesh.stride        = buffer.stride;
	mesh.primitive     = zed_primitive_point_list;
}

void zed_mesh_new_plane( zed_mesh &mesh, int w, int h, float scale ) {
	zed_mesh_vertex *vertices = (zed_mesh_vertex *)malloc( sizeof( zed_mesh_vertex ) * w * h );

	for ( int y = 0; y < h; y++ ) {
	for ( int x = 0; x < w; x++ ) {
		int i = x + y * w;

		vertices[i].position = { x * scale - w * scale / 2.0f, 0, y * scale - h * scale / 2.0f };
		vertices[i].normal = { 0.0f, 1.0f, 0.0f };
	}
	}

	zed_buffer buffer_vertex;

	zed_buffer_new_vertex(
		buffer_vertex,
		vertices,
		sizeof( zed_mesh_vertex ) * w * h,
		sizeof( zed_mesh_vertex )
	);

	free( vertices );

	uint *indices = (uint *)malloc( sizeof( uint ) * w * h * 6 );

	for ( int y = 0; y < h - 1; y++ ) {
	for ( int x = 0; x < w - 1; x++ ) {
		int i = x + y * w;

		indices[ i * 6 + 0 ] = i + w;
		indices[ i * 6 + 1 ] = i + 1;
		indices[ i * 6 + 2 ] = i;

		indices[ i * 6 + 3 ] = i + 1;
		indices[ i * 6 + 4 ] = i + w;
		indices[ i * 6 + 5 ] = i + w + 1;
	}
	}

	zed_buffer buffer_index;

	zed_buffer_new_index(
		buffer_index,
		indices,
		sizeof( uint ) * w * h * 6,
		sizeof( uint )
	);

	mesh.buffer_vertex = buffer_vertex.native;
	mesh.buffer_index  = buffer_index.native;

	mesh.count_vertex  = w * h;
	mesh.count_index   = w * h * 6;

	mesh.stride = sizeof( zed_mesh_vertex );
	mesh.primitive = zed_primitive_triangle_list;
}

void load_mesh_from_mesh_data( zed_mesh &mesh, zed_mesh_data data ) {
	zed_buffer vertex_buffer;

	zed_buffer_new_vertex(
		vertex_buffer,
		data.vertices,
		data.count_vertex * sizeof( zed_mesh_vertex ),
		sizeof( zed_mesh_vertex )
	);

	zed_buffer index_buffer;

	zed_buffer_new_index(
		index_buffer,
		data.indices,
		data.count_index * sizeof( uint ),
		sizeof( uint )
	);

	mesh.buffer_vertex = vertex_buffer.native;
	mesh.buffer_index  = index_buffer.native;
	mesh.count_vertex  = data.count_vertex ;
	mesh.count_index   = data.count_index;
	mesh.stride        = sizeof( zed_mesh_vertex );
	mesh.primitive     = zed_primitive_triangle_list;
}

// todo

#pragma warning( push )
#pragma warning( disable: 4530 )

#pragma warning( push )
#pragma warning( disable: 4626 )
#pragma warning( disable: 4459 )
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader/tiny_obj_loader.h>
#pragma warning( pop )

void zed_mesh_new( zed_mesh &mesh, string file, float scale ) {
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	tinyobj::LoadObj( &attrib, &shapes, &materials, 0, 0, file );

	std::vector<zed_mesh_vertex> vertex_vector;
	std::vector<UINT>            index_vector;

	UINT index_actual = 0;

	// float x_min = std::numeric_limits<float>::max();
	// float y_min = std::numeric_limits<float>::max();
	// float z_min = std::numeric_limits<float>::max();

	// float x_max = std::numeric_limits<float>::lowest();
	// float y_max = std::numeric_limits<float>::lowest();
	// float z_max = std::numeric_limits<float>::lowest();

	// shape
	for ( uint s = 0; s < shapes.size(); s++ ) {
		uint index_offset = 0;

		// face
		for ( uint f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++ ) {
			uint fv = shapes[s].mesh.num_face_vertices[f];

			// vertex
			for ( uint v = 0; v < fv; v++ ) {

				// index
				tinyobj::index_t idx = shapes[s].mesh.indices[ index_offset + v ];

				// position
				float vx   = attrib.vertices[ 3 * idx.vertex_index + 0 ] * scale;
				float vy   = attrib.vertices[ 3 * idx.vertex_index + 1 ] * scale;
				float vz   = attrib.vertices[ 3 * idx.vertex_index + 2 ] * scale;

				// x_min = std::min( x_min, vx );
				// y_min = std::min( y_min, vy );
				// z_min = std::min( z_min, vz );

				// x_max = std::max( x_max, vx );
				// y_max = std::max( y_max, vy );
				// z_max = std::max( z_max, vz );

				// normal
				float nx = 0;
				float ny = 0;
				float nz = 0;

				if ( idx.normal_index >= 0 ) {
					nx = attrib.normals[ 3 * idx.normal_index + 0 ];
					ny = attrib.normals[ 3 * idx.normal_index + 1 ];
					nz = attrib.normals[ 3 * idx.normal_index + 2 ];
				}

				float tx = 0;
				float ty = 0;

				// texture uv
				if ( idx.texcoord_index >= 0 ) {
					tx = attrib.texcoords[ 2 * idx.texcoord_index + 0 ];
					ty = attrib.texcoords[ 2 * idx.texcoord_index + 1 ];
				}

				// vertex colors
				// float r = attrib.colors[ 3 * idx.vertex_index + 0 ];
				// float g = attrib.colors[ 3 * idx.vertex_index + 1 ];
				// float b = attrib.colors[ 3 * idx.vertex_index + 2 ];

				zed_mesh_vertex vertex = {
					float3( vx, vy, vz ),
					float3( nx, ny, nz ),
					float2( tx, ty ),
					// float3( r, g, b )
				};

				vertex_vector.push_back( vertex );
				index_vector.push_back( index_actual );

				index_actual += 1;
			}

			index_offset += fv;

			// per-face material
			// shapes[s].mesh.material_ids[f];
		}
	}

	// note

	// float x_extent = x_max - x_min;
	// float y_extent = y_max - y_min;
	// float z_extent = z_max - z_min;

	// float extent = sqrt( x_extent * x_extent + y_extent * y_extent + z_extent * z_extent );
	// float scale  = 1.0f / extent;

	// for ( uint i = 0; i < vertex_vector.size(); i += 1 ) {
	// 	vertex_vector[i].position.x = ( vertex_vector[i].position.x - ( x_max + x_min ) / 2.0f ) * scale;
	// 	vertex_vector[i].position.y = ( vertex_vector[i].position.y - ( y_max + y_min ) / 2.0f ) * scale;
	// 	vertex_vector[i].position.z = ( vertex_vector[i].position.z - ( z_max + z_min ) / 2.0f ) * scale;
	// }

	// todo move this below
	mesh.count_vertex  = vertex_vector.size();
	mesh.count_index   = index_vector.size();

	zed_buffer buffer_vertex;

	zed_buffer_new_vertex(
		buffer_vertex,
		vertex_vector.data(),
		mesh.count_vertex  * sizeof( zed_mesh_vertex ),
		sizeof( zed_mesh_vertex )
	);

	zed_buffer buffer_index;

	zed_buffer_new_index(
		buffer_index,
		index_vector.data(),
		mesh.count_index * sizeof( uint ),
		sizeof( uint )
	);

	mesh.buffer_vertex = buffer_vertex.native;
	mesh.buffer_index  = buffer_index.native;
	mesh.stride       = sizeof( zed_mesh_vertex );
	mesh.primitive    = zed_primitive_triangle_list;
	// todo
}

#pragma warning( pop )

void zed_mesh_load( zed_mesh &mesh, string path ) {
	// zed_debug_say( "\n" );
	// zed_debug_say( "loading mesh from path: %s\n", path );

	zed_mesh_data data;

	zed_file file = app_system_fopen( path, "rb" );

	app_system_fread( file, (handle)( &data.count_vertex  ), sizeof( uint ), 1 );
	app_system_fread( file, (handle)( &data.count_index   ), sizeof( uint ), 1 );

	// zed_debug_say( "\tvertices_count: %i\n", data.count_vertex  );
	// zed_debug_say( "\tindices_count : %i\n", data.count_index   );
	// zed_debug_say( "\n" );

	// todo use scratch not malloc

	data.vertices = (zed_mesh_vertex *)malloc( data.count_vertex  * sizeof( zed_mesh_vertex ) );
	data.indices  = (uint            *)malloc( data.count_index   * sizeof( uint            ) );

	app_system_fread( file, (handle)( data.vertices ), sizeof( zed_mesh_vertex ), data.count_vertex );
	app_system_fread( file, (handle)( data.indices  ), sizeof( uint            ), data.count_index  );

	app_system_fclose( file );

	load_mesh_from_mesh_data( mesh, data );
}

void zed_mesh_load( zed_mesh &mesh, int id ) {
	zed_mesh_data mesh_data;

	//

	byte *data = (byte *)app_system_resource_data( id );
	int   size =         app_system_resource_size( id );

	//

	mesh_data.count_vertex  = *(uint *)data; data += sizeof( uint );
	mesh_data.count_index   = *(uint *)data; data += sizeof( uint );

	//

	mesh_data.vertices = (zed_mesh_vertex *)malloc( mesh_data.count_vertex * sizeof( zed_mesh_vertex ) );
	mesh_data.indices  = (uint            *)malloc( mesh_data.count_index  * sizeof( uint            ) );

	memcpy( mesh_data.vertices, data, mesh_data.count_vertex * sizeof( zed_mesh_vertex ) ); data += mesh_data.count_vertex * sizeof( zed_mesh_vertex );
	memcpy( mesh_data.indices,  data, mesh_data.count_index  * sizeof( uint            ) ); data += mesh_data.count_index  * sizeof( uint            );

	load_mesh_from_mesh_data( mesh, mesh_data );
}

//

void zed_mesh_draw_primitive( zed_primitive primitive, int count ) {
	app.graphics.device_context->IASetVertexBuffers( 0, 0, 0, 0, 0 );
	app.graphics.device_context->IASetVertexBuffers( 1, 0, 0, 0, 0 );
	// app.graphics.device_context->IASetIndexBuffer( 0, DXGI_FORMAT_R32_UINT, 0 );
	app.graphics.device_context->IASetIndexBuffer( 0, DXGI_FORMAT(0), 0 );
	app.graphics.device_context->IASetPrimitiveTopology( (D3D11_PRIMITIVE_TOPOLOGY)primitive );
	app.graphics.device_context->Draw( count, 0 );
}

void zed_mesh_draw( zed_mesh &mesh ) {
	uint stride = mesh.stride;
	uint offset = 0;

	app.graphics.device_context->IASetVertexBuffers( 0, 1, &mesh.buffer_vertex, &stride, &offset );
	app.graphics.device_context->IASetIndexBuffer( mesh.buffer_index, DXGI_FORMAT_R32_UINT, 0 );
	app.graphics.device_context->IASetPrimitiveTopology( (D3D11_PRIMITIVE_TOPOLOGY)mesh.primitive );

	if ( mesh.buffer_index == 0 ) {
		app.graphics.device_context->Draw( mesh.count_vertex, 0 );
	} else {
		app. graphics.device_context->DrawIndexed( mesh.count_index, 0, 0 );
	}
}

void zed_mesh_draw_instanced( zed_mesh &mesh, zed_buffer *instance_buffer, int count, uint instance_offset ) {
	uint offset = 0;

	app.graphics.device_context->IASetVertexBuffers( 0, 1, &mesh.buffer_vertex, &mesh.stride, &offset );
	if ( instance_buffer ) app.graphics.device_context->IASetVertexBuffers( 1, 1, &instance_buffer->native, &instance_buffer->stride, &instance_offset );
	app.graphics.device_context->IASetIndexBuffer( mesh.buffer_index, DXGI_FORMAT_R32_UINT, 0 );
	app.graphics.device_context->IASetPrimitiveTopology( (D3D11_PRIMITIVE_TOPOLOGY)mesh.primitive );

	if ( mesh.buffer_index == 0 ) {
		app.graphics.device_context->DrawInstanced( mesh.count_vertex, count, 0, 0 );
	} else {
		app. graphics.device_context->DrawIndexedInstanced( mesh.count_index, count, 0, 0, 0 );
	}
}

void zed_mesh_draw_primitive_instanced( zed_primitive primitive, int count, zed_buffer *instance_buffer, int instance_count, uint instance_offset = 0 ) {
	app.graphics.device_context->IASetVertexBuffers( 0, 0, 0, 0, 0 );
	app.graphics.device_context->IASetVertexBuffers( 1, 0, 0, 0, 0 );
	app.graphics.device_context->IASetVertexBuffers( 1, 1, &instance_buffer->native, &instance_buffer->stride, &instance_offset );
	app.graphics.device_context->IASetIndexBuffer( 0, DXGI_FORMAT(0), 0 );
	app.graphics.device_context->IASetPrimitiveTopology( (D3D11_PRIMITIVE_TOPOLOGY)primitive );
	app.graphics.device_context->DrawInstanced( count, instance_count, 0, 0 );
}
