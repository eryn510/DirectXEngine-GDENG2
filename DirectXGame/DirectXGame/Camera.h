#pragma once
#include "AGameObject.h"
#include "InputListener.h"

class Camera : public AGameObject, public InputListener
{
public:
	Camera(std::string name);
	~Camera();

	// Inherited via AGameObject
	virtual void update(float deltaTime) override;
	virtual void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;
	Matrix4x4 getViewMatrix();


	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& mouse_pos) override;
	virtual void onLeftMouseDown(const Point& delta_mouse_pos) override;
	virtual void onLeftMouseUp(const Point& delta_mouse_pos) override;
	virtual void onRightMouseDown(const Point& delta_mouse_pos) override;
	virtual void onRightMouseUp(const Point& delta_mouse_pos) override;

private:
	void updateViewMatrix();

	float ticks = 0.0f;
	float mouseDown = false;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_forward = 0.0f;
	float m_right = 0.0f;
	float m_up = 0.0f;

	float speed = 0.1f;

	Matrix4x4 viewCamera;
};

