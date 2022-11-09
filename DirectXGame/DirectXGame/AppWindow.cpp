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
	//InputSystem::get()->showCursor(false);

	//initialization
	GraphicsEngine::initialize();
	PrimitiveManager::initialize();
	CameraManager::initialize();
	UIManager::initialize(this->m_hwnd);

	//pointer assignment
	graphEngine = GraphicsEngine::getInstance();
	primMngr = PrimitiveManager:: getInstance();
	m_render_system = graphEngine->getRenderSystem();
	m_camera_manager = CameraManager::getInstance();
	m_ui_manager = UIManager::getInstance();
	m_tex_manager = graphEngine->getTextureManager();

	Texture* m_wood_tex = m_tex_manager->createTextureFromFile(L"..\\Assets\\Texture\\wood.jpg");

	RECT rc = this->getClientWindowRect();
	m_swap_chain = m_render_system->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	//NUMBER 1 (SEE Cube.cpp CONSTRUCTOR FOR FURTHER MODIFICATIONS)
	primMngr->create("Cube", CUBE, false);

	//NUMBER 2 (SEE Cube.cpp CONSTRUCTOR FOR FURTHER MODIFICATIONS)
	//primMngr->create("Cube", CUBE, true);

	//NUMBER 3 (SEE Cube.cpp CONSTRUCTOR AND UPDATE FUNCTION FOR FURTHER MODIFICATIONS)
	//primMngr->create("Cube", CUBE, true);

	//NUMBER 4 (SEE Cube.cpp UPDATE FUNCTION FOR FURTHER MODIFICATIONS)
	//primMngr->createMultipleRandom("Cube", CUBE, true, 50);

	//NUMBER 5 (SEE Cube.cpp UPDATE FUNCTION FOR FURTHER MODIFICATIONS)
	//primMngr->create("Cube", CUBE, true);

	/* NUMBER 6 (SEE Cube.cpp CONSTRUCTOR FOR FURTHER MODIFICATIONS)
	primMngr->createWithTransform("Cube", CUBE, Vector3D(0.0, 0.9f, 0.0), TRANSLATION, false);
	primMngr->createWithTransform("Cube", CUBE, Vector3D(-1.5, 2.0f, 0.0), TRANSLATION, false);
	primMngr->createWithTransform("Cube", CUBE, Vector3D(-1.5, 3.0f, -2.0), TRANSLATION, false);
	primMngr->create("Plane", PLANE, false);
	*/
	
	/* NUMBER 7
	//BOTTOM
	AGameObject* card1;
	card1 = primMngr->createWithTransform("Plane", PLANE, Vector3D(3.0, 0.1f, 4.5), SCALE, false);
	card1->setRotation(Vector3D(-5, 0.0, 0.0));
	card1->setPosition(0, 0, 2.25);
	AGameObject* card2;
	card2 = primMngr->createWithTransform("Plane", PLANE, Vector3D(3.0, 0.1f, 4.5), SCALE, false);
	card2->setRotation(Vector3D(5, 0.0, 0.0));
	card2->setPosition(0, 0, 3.75);
	AGameObject* card3;
	card3 = primMngr->createWithTransform("Plane", PLANE, Vector3D(3.0, 0.1f, 4.5), SCALE, false);
	card3->setRotation(Vector3D(-5, 0.0, 0.0));
	card3->setPosition(0, 0, -0.75);
	AGameObject* card4;
	card4 = primMngr->createWithTransform("Plane", PLANE, Vector3D(3.0, 0.1f, 4.5), SCALE, false);
	card4->setRotation(Vector3D(5, 0.0, 0.0));
	card4->setPosition(0, 0, 0.75);
	AGameObject* card5;
	card5 = primMngr->createWithTransform("Plane", PLANE, Vector3D(3.0, 0.1f, 4.5), SCALE, false);
	card5->setRotation(Vector3D(-5, 0.0, 0.0));
	card5->setPosition(0, 0, -3.75);
	AGameObject* card6;
	card6 = primMngr->createWithTransform("Plane", PLANE, Vector3D(3.0, 0.1f, 4.5), SCALE, false);
	card6->setRotation(Vector3D(5, 0.0, 0.0));
	card6->setPosition(0, 0, -2.25);
	AGameObject* card7;
	card7 = primMngr->createWithTransform("Plane", PLANE, Vector3D(3.0, 0.1f, 4.5), SCALE, false);
	card7->setPosition(0, 2.25, -2.25);
	AGameObject* card8;
	card8 = primMngr->createWithTransform("Plane", PLANE, Vector3D(3.0, 0.1f, 4.5), SCALE, false);
	card8->setPosition(0, 2.25, 2.25);

	//MIDDLE
	AGameObject* card9;
	card9 = primMngr->createWithTransform("Plane", PLANE, Vector3D(3.0, 0.1f, 4.5), SCALE, false);
	card9->setRotation(Vector3D(5, 0.0, 0.0));
	card9->setPosition(0, 4.5, 2.25);
	AGameObject* card10;
	card10 = primMngr->createWithTransform("Plane", PLANE, Vector3D(3.0, 0.1f, 4.5), SCALE, false);
	card10->setRotation(Vector3D(5, 0.0, 0.0));
	card10->setPosition(0, 4.5, -0.75);
	AGameObject* card11;
	card11 = primMngr->createWithTransform("Plane", PLANE, Vector3D(3.0, 0.1f, 4.5), SCALE, false);
	card11->setRotation(Vector3D(-5, 0.0, 0.0));
	card11->setPosition(0, 4.5, 0.75);
	AGameObject* card12;
	card12 = primMngr->createWithTransform("Plane", PLANE, Vector3D(3.0, 0.1f, 4.5), SCALE, false);
	card12->setRotation(Vector3D(-5, 0.0, 0.0));
	card12->setPosition(0, 4.5, -2.25);
	AGameObject* card13;
	card13 = primMngr->createWithTransform("Plane", PLANE, Vector3D(3.0, 0.1f, 4.5), SCALE, false);
	card13->setPosition(0, 6.75, 0);

	//UPPER
	AGameObject* card14;
	card14 = primMngr->createWithTransform("Plane", PLANE, Vector3D(3.0, 0.1f, 4.5), SCALE, false);
	card14->setRotation(Vector3D(-5, 0.0, 0.0));
	card14->setPosition(0, 9.0, -0.75);
	AGameObject* card15;
	card15 = primMngr->createWithTransform("Plane", PLANE, Vector3D(3.0, 0.1f, 4.5), SCALE, false);
	card15->setRotation(Vector3D(5, 0.0, 0.0));
	card15->setPosition(0, 9.0, 0.75);
	*/
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

	m_ui_manager->drawAllUI();

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
