#pragma once
#include "Vector3D.h"
#include "Vector2D.h"


class VertexMesh
{
public:
	VertexMesh() :m_position(), m_textcoord()
	{

	}
	VertexMesh(Vector3D position, Vector2D textcoord) :m_position(position), m_textcoord(textcoord)
	{

	}
	VertexMesh(const VertexMesh& vertex) :m_position(vertex.m_position), m_textcoord(vertex.m_textcoord)
	{

	}

	~VertexMesh()
	{

	}

public:
	Vector3D m_position;
	Vector2D m_textcoord;
};