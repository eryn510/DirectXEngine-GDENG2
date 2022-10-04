#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "ConstantBuffer.h"
#include "Cube.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "PrimitiveManager.h"

#include "Vector3D.h"
#include "Matrix4x4.h"


class AppWindow : public Window, public InputListener
{
public:
	void updateQuadPosition();

public:
	static AppWindow* getInstance();
	static void initialize();
	static void destroy();


private:
	AppWindow();
	~AppWindow();
	AppWindow(AppWindow const&) {};
	AppWindow& operator=(AppWindow const&) {};
	static AppWindow* sharedInstance;

public:
	void createGraphicsWindow();

public:
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;
	
	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& delta_mouse_pos) override;
	virtual void onLeftMouseDown(const Point& delta_mouse_pos) override;
	virtual void onLeftMouseUp(const Point& delta_mouse_pos) override;
	virtual void onRightMouseDown(const Point& delta_mouse_pos) override;
	virtual void onRightMouseUp(const Point& delta_mouse_pos) override;

private:
	SwapChain* m_swap_chain;
	VertexShader* m_vs; 
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
	GraphicsEngine* graphEngine;
	PrimitiveManager* primMngr;


private:
	float m_old_delta;
	float m_new_delta;
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;
	
	float m_scale_cube = 1;
	
};

_declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};
