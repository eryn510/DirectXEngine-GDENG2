#pragma once
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "Vector3D.h"

class AppWindow;
class GameObjectManager;

class Quad : public AGameObject
{
public:
	Quad(std::string name);
	~Quad();

public:
	virtual void update(float deltaTime) override;
	virtual void draw(int width, int height) override;
	virtual void setAnimSpeed(float multiplier) override;

protected:
	virtual void awake() override;

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


	Matrix4x4 m_world_cam;

private:
	vertex vertex_list[4] = {};
	void* shader_byte_code;
	size_t size_shader;

private:
	friend class AppWindow;
	friend class GameObjectManager;
};
