#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "PrimitiveManager.h"
#include "CameraManager.h"
#include "UIManager.h"

#include "Vector3D.h"
#include "Matrix4x4.h"


class AppWindow : public Window, public InputListener
{
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
	virtual void onMouseMove(const Point& mouse_pos) override;
	virtual void onLeftMouseDown(const Point& delta_mouse_pos) override;
	virtual void onLeftMouseUp(const Point& delta_mouse_pos) override;
	virtual void onRightMouseDown(const Point& delta_mouse_pos) override;
	virtual void onRightMouseUp(const Point& delta_mouse_pos) override;

private:
	SwapChain* m_swap_chain;
	VertexShader* m_vs; 
	PixelShader* m_ps;

//SINGLETONS
private:
	GraphicsEngine* graphEngine;
	PrimitiveManager* primMngr;
	RenderSystem* m_render_system;
	CameraManager* m_camera_manager;
	UIManager* m_ui_manager;


private:
	float m_delta_time;
	float m_elapsed_time;
	float m_anim_time;
	float m_anim_speed = 1;

	float m_delta_pos;
	float m_delta_scale;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;
	
	float m_scale_cube = 1;

	float m_forward = 0.0f;
	float m_rightward = 0.0f;

	bool isPerspective;

	Matrix4x4 m_world_cam;
	
};

