#include "AppWindow.h"

#include <iostream>

#include "Matrix4x4.h"
#include "InputSystem.h"
#include  <Windows.h>


__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;

};

unsigned int m_time_temp;

AppWindow::AppWindow()
{

	
}

void AppWindow::update()
{
	constant cc;
	cc.m_time = ::GetTickCount();

	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;


	Matrix4x4 temp;

	m_delta_scale += m_delta_time / 0.55f;

	/*	cc.m_world.setIdentity();
		cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));
		temp.setIdentity();
		temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), m_delta_pos));

		cc.m_world *= temp;
		cc.m_world.setIdentity();
		cc.m_world.setScale(Vector3D(m_scale_cube, m_scale_cube, m_scale_cube));

		temp.setIdentity();
		temp.setRotationZ(0.0f);
		cc.m_world *= temp;

		temp.setIdentity();
		temp.setRotationX(m_rot_x);
		cc.m_world *= temp;

		temp.setIdentity();
		temp.setRotationY(m_rot_y);
		cc.m_world *= temp;
		*/

	cam_Ptr->cameraUpdate(m_cb, this->getClientWindowRect());

}


AppWindow::~AppWindow()
{
}


void AppWindow::onCreate()
{
	
	Window::onCreate();

	InputSystem::get()->addListener(this);
	InputSystem::get()->showCursor(false);

	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	//creating triangles with determined positions

	m_world_cam.setTranslation(Vector3D(0, 0, -2));

	vertexPard test_vertex[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }
	};
	vertex list[] =
	{
		//X - Y - Z
		{-0.5f,-0.5f,0.0f,    -0.32f,-0.11f,0.0f,   0,0,0,  0,1,0 }, // POS1
		{-0.5f,0.5f,0.0f,     -0.11f,0.78f,0.0f,    1,1,0,  0,1,1 }, // POS2
		{ 0.5f,-0.5f,0.0f,     0.75f,-0.73f,0.0f,   0,0,1,  1,0,0 },// POS2
		{ 0.5f,0.5f,0.0f,      0.88f,0.77f,0.0f,    1,1,1,  0,0,1 }
	};
	/*
	vertex list1[] =
	{
		//X - Y - Z
		{-0.75f,-0.5f,0.0f,   1,0,1}, // POS1
		{-0.75f,0.5f,0.0f,    1,0,1}, // POS2
		{ 0.0f,-0.5f,0.0f,   1,0,1},// POS2
		{ 0.0f,0.5f,0.0f,    1,0,1}
	};
	vertex list2[] =
	{
		//X - Y - Z
		{0.0f,0.5f,0.0f,   1,1,0}, // POS1
		{0.0f,0.9f,0.0f,    1,1,0}, // POS2
		{ 0.9f,0.5f,0.0f,   1,1,0},// POS2
		{ 0.9f,0.9f,0.0f,    1,1,0}
	};
	vertex list3[] =
	{
		//X - Y - Z
		{0.3f,-0.8f,0.0f,   1,0,0}, // POS1
		{0.3f,0.0f,0.0f,    1,0,0}, // POS2
		{ 0.8f,-0.8f,0.0f,   1,0,0},// POS2
		{ 0.8f,0.0f,0.0f,    1,0,0}
	};
	*/
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(test_vertex);

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	m_ib = GraphicsEngine::get()->createIndexBuffer();

	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->load(index_list, size_index_list);


	void *shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	//GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);
	m_vb->load(test_vertex, sizeof(vertexPard), size_list, shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
	/*
	quadOne.init(&list1);
	quadTwo.init(&list2);
	quadThree.init(&list3);
	quadOne.drawMesh();
*/
	
	constant cc;
	cc.m_time = 0;
	m_time_temp = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	//m_cb->load(&cc, sizeof(constant));
	m_cb->load(&m_time_temp, sizeof(constant));

	cam_1.initializeCamera(true);
	cam_2.initializeCamera(false);

	m_world_cam2.setTranslation(Vector3D(0, 0, -2));
	m_world_cam.setTranslation(Vector3D(0, 0, -2));

	camPtr = &m_world_cam;

	cam_Ptr = &cam_1;

	//m_rs = GraphicsEngine::get()->createRasterizer_state();

}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//GraphicsEngine::get()->createRasterizer_state();


	update();

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);



	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	//set indices
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	//  DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->setRasterizerState(cam_Ptr->m_rs);

	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);/**/
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexTriangleList(m_ib->getSizeIndexList(),0, 0);
	//quadOne.drawQuad();

	/*
	quadOne.drawQuad();
	quadTwo.drawQuad();
	quadThree.drawQuad();
	*/
	m_swap_chain->present(true);


	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();

	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_ib->release();
	m_cb->release();
	
	m_swap_chain->release();
	
	/*quadOne.release();
	quadTwo.release();
	quadThree.release();
	*/
	m_ps->release();
	m_vs->release();
	GraphicsEngine::get()->release();

}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		//m_rot_x += 3.14f * m_delta_time;
		cam_Ptr->m_forward = 1.0f;
	}
	else if (key == 'S')
	{
		cam_Ptr->m_forward = -1.0f;

		//m_rot_x -= 3.14f * m_delta_time;
	}
	else if (key == 'A')
	{
		cam_Ptr->m_rightward = -1.0f;

		//m_rot_y += 3.14f * m_delta_time;
	}
	else if (key == 'D')
	{
		cam_Ptr->m_rightward = 1.0f;

		//m_rot_y -= 3.14f * m_delta_time;
	}

	else if (key == 'E')
	{
		cam_Ptr = &cam_1;
		GraphicsEngine::get()->getImmediateDeviceContext()->setRasterizerState(cam_Ptr->m_rs);

		//camPtr = &m_world_cam2;
	}

	else if (key == 'R')
	{
		cam_Ptr = &cam_2;
		GraphicsEngine::get()->getImmediateDeviceContext()->setRasterizerState(cam_Ptr->m_rs);

		//camPtr = &m_world_cam;
	}


}

void AppWindow::onKeyUp(int key)
{
	cam_Ptr->m_forward = 0.0f;
	cam_Ptr->m_rightward = 0.0f;

}

void AppWindow::onMouseMove(const Point& mouse_pos)
{

	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	
	cam_Ptr->m_rot_x += (mouse_pos.m_y - (height / 2.0f)) * m_delta_time * 0.1f;
	cam_Ptr->m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * m_delta_time * 0.1f;

	InputSystem::get()->setCursorPosition(Point(width / 2.0f, height / 2.0f));
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
	m_scale_cube = 0.5f;
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
	m_scale_cube = 1.0f;
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
	m_scale_cube = 2.0f;
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
	m_scale_cube = 1.0f;
}