#include "Camera.h"

#include "GraphicsEngine.h"
#include "InputSystem.h"
#include "DeviceContext.h"


__declspec(align(16))
struct perspective
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;

};


Camera::Camera()
{
}

void Camera::cameraUpdate(ConstantBuffer* m_cb, RECT rc)
{

	perspective cc;

	cc.m_time = ::GetTickCount();

	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;


	Matrix4x4 temp;

	m_delta_scale += m_delta_time / 0.55f;


		cc.m_world.setIdentity();
		cc.m_world.setScale(Vector3D(100, 100, 100));
		cc.m_world.setScale(Vector3D(1, 1, 1));

		/*cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));
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
	//cc.m_world.setIdentity();

	Matrix4x4 world_cam;
	world_cam.setIdentity();


	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	world_cam *= temp;
	/**/


	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.3f);
	new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.1f);
	world_cam.setTranslation(new_pos);
/*
	*posPtr = camPtr->getTranslation() + world_cam.getZDirection() * (m_forward * 0.3f);
	*posPtr = *posPtr + world_cam.getXDirection() * (m_rightward * 0.1f);
	world_cam.setTranslation(*posPtr);
*/


	//world_cam.setTranslation(Vector3D(0, 0, -2.0f));
	m_world_cam = world_cam;

	world_cam.inverse();


	//cc.m_view.setIdentity();
	cc.m_view = world_cam;
	localMatrix = world_cam;
	/*
	cc.m_proj.setOrthoLH
	(
		(rc.right - rc.left) / 400.0f,
		(rc.bottom - rc.top) / 400.0f,
		-4.0f,
		4.0f
	);
	*/

	int width = (rc.right - rc.left);
	int height = (rc.bottom - rc.top);


	//cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), -10.0f, 2.0f);


	//m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

void Camera::initializeCamera(bool wireframe)
{
	m_rs = GraphicsEngine::get()->createRasterizer_state(wireframe);

	m_world_cam.setTranslation(Vector3D(0, 0, -4.f));

}

Matrix4x4 Camera::getViewMatrix()
{

	return this->localMatrix;
}
