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
}

void AppWindow::destroy()
{
	if (sharedInstance != NULL)
	{
		sharedInstance->~AppWindow();
	}
}

AppWindow::~AppWindow()
{
}

void AppWindow::createGraphicsWindow()
{
	GraphicsEngine::initialize();
	graphEngine = GraphicsEngine::getInstance();
	PrimitiveManager::initialize();
	primMngr = PrimitiveManager:: getInstance();
	m_render_system = graphEngine->getRenderSystem();
	CameraManager::initialize();
	m_camera_manager = CameraManager::getInstance();

	InputSystem::get()->addListener(this);
	InputSystem::get()->showCursor(false);

	RECT rc = this->getClientWindowRect();
	m_swap_chain = m_render_system->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);


	//m_world_cam.setTranslation(Vector3D(0.0f, 0.0f, -2.0f));

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	//Vertex Shader
	m_render_system->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = m_render_system->createVertexShader(shader_byte_code, size_shader);

	primMngr->create("Cube", shader_byte_code, size_shader, CUBE);
	primMngr->create("Plane", shader_byte_code, size_shader, PLANE);

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

	//update();

	m_camera_manager->update();


	for (auto cube : primMngr->cube_list) 
	{
		cube->update(EngineTime::getDeltaTime());
		cube->draw(width, height, this->m_vs, this->m_ps);
	}

	for (auto quad : primMngr->quad_list) 
	{
		quad->update(EngineTime::getDeltaTime());
		quad->draw(width, height, this->m_vs, this->m_ps);
	}

	for (auto circle : primMngr->circle_list) 
	{
		circle->update(EngineTime::getDeltaTime());
		circle->draw(width, height, this->m_vs, this->m_ps);
	}

	for (auto plane : primMngr->plane_list)
	{
		plane->update(EngineTime::getDeltaTime());
		plane->draw(width, height, this->m_vs, this->m_ps);
	}

	
	m_swap_chain->present(true);

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	graphEngine->destroy();
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
	if (key == 'W')
	{
		//m_rot_x += 3.14f * m_delta_time;
		m_forward = 1.0f;
	}
	else if (key == 'S')
	{
		//m_rot_x -= 3.14f * m_delta_time;
		m_forward = -1.0f;
	}
	if (key == 'A')
	{
		//m_rot_y += 3.14f * m_delta_time;
		m_rightward = -1.0f;
	}
	else if (key == 'D')
	{
		//m_rot_y -= 3.14f * m_delta_time;
		m_rightward = 1.0f;
	}
}

void AppWindow::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_rightward = 0.0f;
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	m_rot_x += (mouse_pos.m_y - (height / 2.0f)) * m_delta_time * 0.1f;
	m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * m_delta_time * 0.1f;

	m_input->setCursorPosition(Point(width / 2.0f, height / 2.0f));
}

void AppWindow::onLeftMouseDown(const Point& delta_mouse_pos)
{
	m_scale_cube = 0.5f;
}

void AppWindow::onLeftMouseUp(const Point& delta_mouse_pos)
{
	m_scale_cube = 1.0f;
}

void AppWindow::onRightMouseDown(const Point& delta_mouse_pos)
{
	m_scale_cube = 2.0f;
}

void AppWindow::onRightMouseUp(const Point& delta_mouse_pos)
{
	m_scale_cube = 1.0f;
}
