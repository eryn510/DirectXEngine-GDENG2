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


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	//Vertex Shader
	m_render_system->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = m_render_system->createVertexShader(shader_byte_code, size_shader);

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

	primMngr->create("Cube", shader_byte_code, size_shader, CUBE);
	primMngr->create("Plane", shader_byte_code, size_shader, PLANE);
	primMngr->create("Circle", shader_byte_code, size_shader, CIRCLE);

	m_render_system->releaseCompiledShader();

	//Pixel Shader
	m_render_system->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = m_render_system->createPixelShader(shader_byte_code, size_shader);
	m_render_system->releaseCompiledShader();

}


void AppWindow::onCreate()
{

}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	m_render_system->getImmediateDeviceContext()->setVertexShader(this->m_vs);
	m_render_system->getImmediateDeviceContext()->setPixelShader(this->m_ps);
	//CLEAR RENDER TARGET
	m_render_system->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.5f, 0.5f, 1);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	float width = rc.right - rc.left;
	float height = rc.bottom - rc.top;
	m_render_system->getImmediateDeviceContext()->setViewportSize(width, height);

	m_camera_manager->update();

	primMngr->update(width, height, this->m_vs, this->m_ps);

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
