#include "RasterizerState.h"
#include "GraphicsEngine.h"


RasterizerState::RasterizerState()
{
}

void RasterizerState::release()
{
	m_rs->Release();
	delete this;
}

bool RasterizerState::init()
{
	D3D11_RASTERIZER_DESC rasterizer_desc;
	ZeroMemory(&rasterizer_desc, sizeof(D3D11_RASTERIZER_DESC));

	rasterizer_desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
	rasterizer_desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;


	if (!SUCCEEDED(GraphicsEngine::get()->m_d3d_device->CreateRasterizerState(&rasterizer_desc, &m_rs)))
		return false;

	return true;

}

RasterizerState::~RasterizerState()
{
}
