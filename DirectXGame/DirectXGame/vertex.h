#pragma once
#include "Vector3D.h"

struct vec3
{
	float x, y, z;

};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};
struct vertexPard
{
	Vector3D position;
	//Vector3D position1;
	Vector3D color;
	Vector3D color1;

};

__declspec(align(16))
struct angle
{
	float m_angle;
};