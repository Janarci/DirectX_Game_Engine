#pragma once
#include "VertexBuffer.h"
#include "DeviceContext.h"
#include "GraphicsEngine.h"
#include "vertex.h"
#include "VertexShader.h"
#include "PixelShader.h"



class Quad
{
public:
	void drawQuad();
	void drawMesh();
	//void init(struct vertex *list);
	void init(vertex(* info)[4]);
	void release();

	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;


};

