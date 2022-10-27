#include "AppWindow.h"
#include <Windows.h>
#include "InputSystem.h"
#include "MathUtils.h"

AppWindow* AppWindow::sharedInstance = NULL;

AppWindow::AppWindow()
{
}

AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	sharedInstance->init();
}

void AppWindow::destroy()
{
	if (sharedInstance != NULL)
	{
		sharedInstance->release();
	}
}


AppWindow::~AppWindow()
{
}

void AppWindow::createGraphicsWindow()
{
	InputSystem::get()->addListener(this);
	InputSystem::get()->showCursor(false);

	GraphicsEngine::initialize();
	graphEngine = GraphicsEngine::getInstance();
	PrimitiveManager::initialize();
	primMngr = PrimitiveManager:: getInstance();
	m_render_system = graphEngine->getRenderSystem();
	CameraManager::initialize();
	m_camera_manager = CameraManager::getInstance();

	RECT rc = this->getClientWindowRect();
	m_swap_chain = m_render_system->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	/*
	for (int i = 0; i < 100; i++) {
		float x = MathUtils::randomFloat(-0.75, 0.75);
		float y = MathUtils::randomFloat(-0.75, 0.75);
		float z = MathUtils::randomFloat(-0.75, 0.75);


		primMngr->create("Cube", shader_byte_code, size_shader, CUBE); 
		primMngr->cube_list.back()->setAnimSpeed(MathUtils::randomFloat(-3.75, 3.75));
		primMngr->cube_list.back()->setPosition(x, y, z);
		primMngr->cube_list.back()->setScale(0.25f, 0.25f, 0.25f);
	}
	*/

	primMngr->create("Cube", CUBE);
	primMngr->create("Plane", PLANE);
	//primMngr->create("Circle", shader_byte_code, size_shader, CIRCLE);
}


void AppWindow::onCreate()
{

}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	//CLEAR RENDER TARGET
	m_render_system->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.5f, 0.5f, 1);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	float width = rc.right - rc.left;
	float height = rc.bottom - rc.top;
	m_render_system->getImmediateDeviceContext()->setViewportSize(width, height);

	m_camera_manager->update();

	primMngr->update(width, height);

	m_swap_chain->present(true);

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	graphEngine->release();
	primMngr->release();
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	
}

void AppWindow::onKeyUp(int key)
{
	
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	
}

void AppWindow::onLeftMouseDown(const Point& delta_mouse_pos)
{
	
}

void AppWindow::onLeftMouseUp(const Point& delta_mouse_pos)
{
	
}

void AppWindow::onRightMouseDown(const Point& delta_mouse_pos)
{
	
}

void AppWindow::onRightMouseUp(const Point& delta_mouse_pos)
{
	
}
