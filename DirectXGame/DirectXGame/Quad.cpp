#include "Quad.h"


void Quad::drawQuad()
{
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);

}

void Quad::drawMesh()
{

	vertex list[] =
	{
		//X - Y - Z
		{-0.5f,-0.5f,0.0f,   1,0,0}, // POS1
		{-0.5f,0.5f,0.0f,    0,1,0}, // POS2
		{ 0.5f,-0.5f,0.0f,   0,0,1},// POS2
		{ 0.5f,0.5f,0.0f,    1,1,0},
		{ 0.7f,-0.5f,0.0f,    1,1,0},
		{ 0.7f,0.5f,0.0f,    1,1,0},

	}; 

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	//GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	//GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();



}

void Quad::init(vertex(* info)[4])
{
	/*
	vertex list[] =
	{
		//X - Y - Z
		{-0.5f,-0.5f,0.0f,   1,0,0}, // POS1
		{-0.5f,0.5f,0.0f,    0,1,0}, // POS2
		{ 0.5f,-0.5f,0.0f,   0,0,1},// POS2
		{ 0.5f,0.5f,0.0f,    1,1,0}
	};*/

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(*info);

	//GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	//GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);
	m_vb->load(info, sizeof(vertex), size_list, shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();
}

void Quad::release()
{
	m_vb->release();
	m_ps->release();
	m_vs->release();
}
