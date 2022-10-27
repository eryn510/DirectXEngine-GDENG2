#pragma once
#include "Cube.h"
#include "Prerequisites.h"

class AppWindow;
class PrimitiveManager;

class Plane : public Cube
{
public:
	Plane(std::string name);
	~Plane();

public:
	virtual void update(float deltaTime) override;
	virtual void draw(int width, int height) override;
	void setAnimSpeed(float multiplier);

public:
	RenderSystem* m_system = GraphicsEngine::getInstance()->getRenderSystem();

private:
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	ConstantBuffer* m_cb;
	VertexShader* m_vs;
	PixelShader* m_ps;

private:
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float speed = 1.0f;
	float elapsedTime = 0.0f;
	float animSpeed = 1.0f;

private:
	vertex vertex_list[8] = {};
	void* shader_byte_code;
	size_t size_shader;

private:
	friend class AppWindow;
	friend class PrimitiveManager;
};

