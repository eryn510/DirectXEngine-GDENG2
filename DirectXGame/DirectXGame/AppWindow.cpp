#include "AppWindow.h"
#include <Windows.h>
#include "InputSystem.h"
#include "MathUtils.h"
#include "ShaderLibrary.h"
#include "Mesh.h"
#include "PhysicsSystem.h"


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


void AppWindow::initializeEngine() 
{
	InputSystem::get()->addListener(this);
	//InputSystem::get()->showCursor(false);

	//initialization
	GraphicsEngine::initialize();
	GameObjectManager::initialize();
	CameraManager::initialize();
	ShaderLibrary::initialize();
	UIManager::initialize(this->m_hwnd);
	BaseComponentSystem::initialize();


	//pointer assignment
	graphEngine = GraphicsEngine::getInstance();
	objMngr = GameObjectManager::getInstance();
	m_render_system = graphEngine->getRenderSystem();
	m_camera_manager = CameraManager::getInstance();
	m_ui_manager = UIManager::getInstance();
	m_tex_manager = graphEngine->getTextureManager();
	m_mesh_manager = graphEngine->getMeshManager();
	m_component_system = BaseComponentSystem::getInstance();


	RECT rc = this->getClientWindowRect();
	m_swap_chain = m_render_system->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
}

void AppWindow::Start()
{
	m_text = m_tex_manager->createTextureFromFile(L"Assets\\Textures\\brick.png");

	AGameObject* gameObject;
	//primMngr->create("Cube", CUBE, false, m_text);
	for (int i = 0; i < 20; i++) {
		gameObject = objMngr->create("Cube", CUBE, false);
	}
	
	objMngr->create("Plane", PLANE, false);
}


void AppWindow::onCreate()
{

}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	m_component_system->getPhysicsSystem()->updateAllComponents();

	//CLEAR RENDER TARGET
	m_render_system->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.5f, 0.5f, 1);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	float width = rc.right - rc.left;
	float height = rc.bottom - rc.top;
	m_render_system->getImmediateDeviceContext()->setViewportSize(width, height);

	m_camera_manager->update();

	objMngr->update(width, height);

	m_ui_manager->drawAllUI();

	m_swap_chain->present(true);

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	graphEngine->release();
	objMngr->release();
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
