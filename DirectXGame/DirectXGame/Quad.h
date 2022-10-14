#pragma once
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "Vector3D.h"

class AppWindow;
class PrimitiveManager;

class Quad : public AGameObject
{
public:
	Quad(std::string name, void* shader_byte_code, size_t size_shader);
	~Quad();

public:
	virtual void update(float deltaTime) override;
	virtual void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void setAnimSpeed(float deltaTime);

public:
	RenderSystem* m_system = GraphicsEngine::getInstance()->getRenderSystem();

private:
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	ConstantBuffer* m_cb;

private:
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;

private:
	vertex vertex_list[4] = {};
	void* shader_byte_code;
	size_t size_shader;

private:
	friend class AppWindow;
	friend class PrimitiveManager;
};
