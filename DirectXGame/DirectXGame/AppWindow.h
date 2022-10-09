#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Quad.h"
#include "vertex.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "InputListener.h"
#include "Matrix4x4.h"
#include "Camera.h"
#include "RasterizerState.h"
#include "EngineTime.h"



class AppWindow : public Window, public InputListener
{
public:
	AppWindow();

	void update();

	~AppWindow();



	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	void onFocus() override;
	void onKillFocus() override;

	void onKeyDown(int key) override;
	void onKeyUp(int key) override;

	void onMouseMove(const Point& mouse_pos) override;
	void onLeftMouseDown(const Point& mouse_pos) override;
	void onLeftMouseUp(const Point& mouse_pos) override;
	void onRightMouseDown(const Point& mouse_pos) override;
	void onRightMouseUp(const Point& mouse_pos) override;
	

private:

	Quad quadOne;
	Quad quadTwo;
	Quad quadThree;

	SwapChain *m_swap_chain;
	VertexBuffer *m_vb;
	VertexShader *m_vs;
	PixelShader *m_ps;
	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;
	RasterizerState* m_rs;


private:
	long m_old_delta;
	long m_new_delta;

	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = 1;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_scale_cube = 1.0f;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;

	Matrix4x4 m_world_cam;
	Vector3D cam1_pos;

	Matrix4x4 m_world_cam2;
	Vector3D cam2_pos;

	Matrix4x4* camPtr;

	Camera cam_1;
	Camera cam_2;
	Camera* cam_Ptr;
};
