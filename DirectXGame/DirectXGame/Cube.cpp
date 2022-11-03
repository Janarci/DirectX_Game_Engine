#include "Cube.h"

#include <iostream>

#include "Camera.h"
#include "DeviceContext.h"
#include "GraphicsEngine.h"
#include "InputSystem.h"
#include "SwapChain.h"

Cube::Cube(string name, void* shaderByteCode, size_t sizeShader, ConstantBuffer* constantBuffer) :AGameObject(name)
{
	
	Vertex quadList[] = {
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

	this->vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	this->vertexBuffer->load(quadList, sizeof(Vertex), ARRAYSIZE(quadList), shaderByteCode, sizeShader);

	unsigned int indexList[] =
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
	this->indexBuffer = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(indexList);
	this->indexBuffer->load(indexList, size_index_list);

	//create constant buffer
	Data data = {};
	data.time = 0;

	//this->m_cb = GraphicsEngine::get()->createConstantBuffer();
	//this->m_cb->load(&data, sizeof(data));

	//this->m_cb = constantBuffer;
	constantBuffer->load(&data, sizeof(data));
	//this->m_cb = m_cb;




}

Cube::~Cube()
{
	this->vertexBuffer->release();
	this->indexBuffer->release();
	AGameObject::~AGameObject();
}

void Cube::update(float deltaTime)
{

}

void Cube::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader, ConstantBuffer* constantBuffer, Camera* cam)
{

	Data cbData = {};
	//cbData.time = this->ticks * this->speed;
	this->deltaPos += this->deltaTime / 10.0f;

	if (this->deltaPos > 1.0f) {
		this->deltaPos = 0.0f;
	}
		
	

	Matrix4x4 temp;
	m_delta_rot += deltaTime / 0.55f;

	//cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));

	//temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f,1.5f, 0), m_delta_pos));

	//cc.m_world *= temp;
	
	cbData.worldMatrix.setIdentity();
	cbData.worldMatrix.setScale(this->getLocalScale());

	//for rotations
	temp.setIdentity();
	temp.setRotationZ(m_delta_rot);
	//cbData.worldMatrix *= temp;

	//for rotations
	temp.setIdentity();
	temp.setRotationY(m_delta_rot);
	//cbData.worldMatrix *= temp;

	//for rotations
	temp.setIdentity();
	temp.setRotationX(m_delta_rot);
	//cbData.worldMatrix *= temp;


	temp.setIdentity();
	temp.setTranslation(this->getLocalPosition());

	cbData.worldMatrix *= temp;
	//cbData.worldMatrix.setIdentity();



	cbData.viewMatrix.setIdentity();
	cbData.viewMatrix = cam->getViewMatrix();
	/*
	cbData.projMatrix.setOrthoLH
	(
		width / 300.0f,
		height / 300.0f,
		-4.0f,
		4.0f
	);
	*/
	cbData.projMatrix.setPerspectiveFovLH(((float)width / (float)height), ((float)width / (float)height), 0.1f, 100.0f);
	//cbData.projMatrix.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);
	
	constantBuffer->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cbData);

	
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, constantBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, constantBuffer);

	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(this->indexBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->vertexBuffer);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexTriangleList(this->indexBuffer->getSizeIndexList(), 0, 0);

	oldTime = newDelta;
	newDelta = ::GetTickCount();

	deltaTime = (oldTime) ? ((newDelta  - oldTime) / 1000.0f) : 0;
}
