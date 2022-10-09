#pragma once
#include "ConstantBuffer.h"
#include "InputListener.h"
#include "Matrix4x4.h"

class Camera
{

public:
	Camera();

	void cameraUpdate(ConstantBuffer* m_cb, RECT rc);
	void initializeCamera();

	long m_old_delta;
	long m_new_delta;
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;


	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_scale_cube = 1.0f;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;

	Matrix4x4 m_world_cam;
	Vector3D m_cam_pos;




};

