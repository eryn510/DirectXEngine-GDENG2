#pragma once
#include "Vector2D.h"


class Vector3D
{
public:
	Vector3D() :m_x(0), m_y(0), m_z(0)
	{
		
	}
	Vector3D(float x, float y, float z) :m_x(x), m_y(y), m_z(z)
	{

	}
	Vector3D(const Vector3D &vector) :m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z)
	{

	}

	static Vector3D lerp(const Vector3D& start, const Vector3D& end, float delta)
	{
		Vector3D v;
		v.m_x = start.m_x * (1.0f - delta) + end.m_x * (delta);
		v.m_y = start.m_y * (1.0f - delta) + end.m_y * (delta);
		v.m_z = start.m_z * (1.0f - delta) + end.m_z * (delta);

		return v;
	}

	static Vector3D zeros()
	{
		Vector3D v;

		v.m_x = 0.0f;
		v.m_y = 0.0f;
		v.m_z = 0.0f;

		return v;
	}

	static Vector3D ones()
	{
		Vector3D v;

		v.m_x = 1.0f;
		v.m_y = 1.0f;
		v.m_z = 1.0f;

		return v;
	}

	Vector3D operator *(float num)
	{
		return Vector3D(m_x * num, m_y * num, m_z * num);
	}

	Vector3D operator +(Vector3D vec)
	{
		return Vector3D(m_x + vec.m_x, m_y + vec.m_y, m_z + vec.m_z);
	}

	bool operator <(Vector3D vec)
	{
		if (m_x < vec.m_x && m_y < vec.m_y && m_z < vec.m_z)
			return true;
		else
			return false;
		
	}

	~Vector3D()
	{
		
	}

public:
	float m_x, m_y, m_z;
};

struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

struct texturevertex {
	Vector3D position;
	Vector2D texCoord;
};

