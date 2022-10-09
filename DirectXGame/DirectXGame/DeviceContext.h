#pragma once
#include <d3d11.h>

class SwapChain;
class VertexBuffer;
class IndexBuffer;
class VertexShader;
class PixelShader;
class ConstantBuffer;
class RasterizerState;

class DeviceContext
{

public:
	DeviceContext(ID3D11DeviceContext* device_context);
	~DeviceContext();

	void clearRenderTargetColor(SwapChain *swap_chain, float red, float green, float blue, float alpha);

	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
	void setViewportSize(UINT width, UINT height);
	void setRasterizerState(RasterizerState* rasterizerState);

	void setVertexShader(VertexShader *vertex_shader);
	void setPixelShader(PixelShader* pixel_shader);

	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void setIndexBuffer(IndexBuffer* index_buffer);
	void setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* buffer);
	void setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* buffer);


	bool release();

private:
	ID3D11DeviceContext* m_device_context;

private:
	friend class ConstantBuffer;
};

