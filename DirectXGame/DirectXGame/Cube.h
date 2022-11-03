#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

class Cube : public AGameObject
{
public:
	Cube(string name, void* shaderByteCode, size_t sizeShader, ConstantBuffer* constantBuffer);
	~Cube();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader, ConstantBuffer* constantBuffer, Camera* cam) override;

private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	//ConstantBuffer* m_cb;
	float m_delta_rot;
	long oldTime;
	long newDelta;

	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;
};