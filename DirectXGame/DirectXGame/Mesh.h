#pragma once
#include "Resource.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Mesh : public Resource
{
public:
	Mesh(const wchar_t* full_path);
	~Mesh();

	VertexBuffer* getVertexBuffer();
	IndexBuffer* getIndexBuffer();

	void setTexture(Texture* texture);
	void draw();

private:
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	Texture* m_texture;

private:
	friend class DeviceContext;
};

