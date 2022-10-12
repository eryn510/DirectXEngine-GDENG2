#pragma once
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "Vector3D.h"

class AppWindow;
class PrimitiveManager;

class Circle : public AGameObject
{
public:
	Circle(float radius, Vector3D centerVertex, void* shader_byte_code, size_t size_shader);
	~Circle();

public:
	virtual void create() override;
	virtual void update() override;
	virtual void release() override;
	void setAnimSpeed(float deltaTime);

public:
	RenderSystem* m_system = GraphicsEngine::getInstance()->getRenderSystem();

private:
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	ConstantBuffer* m_cb;

private:
	static const int arcCount = 60;
	Vector3D centerPoint;
	float radius;

private:
	vertex vertex_list[arcCount] = {};
	void* shader_byte_code;
	size_t size_shader;


private:
	friend class AppWindow;
	friend class PrimitiveManager;
};

