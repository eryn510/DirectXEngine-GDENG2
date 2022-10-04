#pragma once
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "Vector3D.h"


struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

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
	VertexBuffer* cube_vb;
	IndexBuffer* cube_ib;
	ConstantBuffer* cube_cb;

private:
	vertex vertex_list[8] = {};
	void* shader_byte_code;
	size_t size_shader;

private:
	friend class AppWindow;
	friend class PrimitiveManager;
};



