#include <zed/app.h>
#include <zed/app/graphics.h>
#include <zed/platform/d3d11.h>

void app_graphics_input_layout_init() {
	D3D11_INPUT_ELEMENT_DESC ied[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// todo needs to be validated against a dummy shader

	// app.graphics.device->CreateInputLayout( ied, 1, 0, 0, (ID3D11InputLayout **)&input_layouts.p   );
	// app.graphics.device->CreateInputLayout( ied, 2, 0, 0, (ID3D11InputLayout **)&input_layouts.pn  );
	// app.graphics.device->CreateInputLayout( ied, 3, 0, 0, (ID3D11InputLayout **)&input_layouts.pnt );
}
