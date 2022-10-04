#pragma once
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "Vector3D.h"

class AppWindow;
class PrimitiveManager;

class Cube : public AGameObject
{
public:
	Cube(vertex vertex_list[], void* shader_byte_code, size_t size_shader);
	~Cube();

public:
	virtual void create() override;
	virtual void update() override;
	virtual void release() override;
	void setAnimSpeed(float deltaTime);

public:
	GraphicsEngine *graphEngine = GraphicsEngine::getInstance();

private:
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	ConstantBuffer* m_cb;

private:
	vertex vertex_list[8] = {};
	void* shader_byte_code;
	size_t size_shader;

private:
	friend class AppWindow;
	friend class PrimitiveManager;
};



