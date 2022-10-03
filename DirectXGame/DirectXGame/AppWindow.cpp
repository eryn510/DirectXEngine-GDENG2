#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "GraphicsEngine.h"

#include "DeviceContext.h"


struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

_declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};

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

void AppWindow::updateQuadPosition()
{
	constant cc;
	cc.m_time = ::GetTickCount();

	m_delta_pos += m_delta_time / 10.0f;

	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;


	Matrix4x4 temp;

	/*
	//NO INPUT
	cc.m_world.setTranslation(Vector3D::lerp(Vector3D(-2, -2, 0), Vector3D(2, 2, 0), m_delta_pos));

	m_delta_scale += m_delta_time / 0.55f;

	cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5f, 0.5f, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));

	temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), m_delta_pos));

	cc.m_world *= temp;

	*/

	//*
	//WITH INPUT
	cc.m_world.setScale(Vector3D(m_scale_cube, m_scale_cube, m_scale_cube));


	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationZ(0.0f);
	cc.m_world *= temp;
	//*/


	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left) / 300.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 300.0f,
		-4.0f,
		4.0f
	);


	m_cb->update(graphEngine->getImmediateDeviceContext(), &cc);
}

AppWindow::~AppWindow()
{
}

void AppWindow::createGraphicsWindow()
{
	InputSystem::get()->addListener(this);

	GraphicsEngine::initialize();
	graphEngine = GraphicsEngine::getInstance();

	m_swap_chain = graphEngine->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	///*
	//RECTANGLE RAINBOW
	vertex vertex_list[]
	{
		//	X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f, -0.5f, -0.5f),	Vector3D(1,0,0),    Vector3D(0.2f,0,0)}, //POS1
		{Vector3D(-0.5f, 0.5f, -0.5f),		Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0)}, //POS2
		{Vector3D(0.5f, 0.5f, -0.5f),		Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0)}, //POS3
		{Vector3D(0.5f, -0.5f, -0.5f),		Vector3D(1,0,0),    Vector3D(0.2f,0,0)}, //POS4

		//BACK FACE
		{Vector3D(0.5f, -0.5f, 0.5f),		Vector3D(0,1,0),    Vector3D(0,0.2f,0)}, //POS5
		{Vector3D(0.5f, 0.5f, 0.5f),		Vector3D(0,1,1),    Vector3D(0,0.2f,0.2f)}, //POS6
		{Vector3D(-0.5f, 0.5f, 0.5f),		Vector3D(0,1,1),    Vector3D(0,0.2f,0.2f)}, //POS7
		{Vector3D(-0.5f, -0.5f, 0.5f),		Vector3D(0,1,0),    Vector3D(0,0.2f,0)} //POS8
	};
	//*/

	/*
	//TRIANGLE RAINBOW
	vertex list[]
	{
		//	X - Y - Z	TRI
		{-0.5, -0.5, 0.0f,		1,0,0}, //POS1
		{0, 0.5, 0.0f,		0,1,0}, //POS2
		{0.5, -0.5, 0.0f,		0,0,1}, //POS3
	};
	*/

	/*
	//RECTANGLE GREEN
	vertex list[]
	{
		//	X - Y - Z	QUAD
		{-0.5, -0.5, 0.0f,		0,1,0}, //POS1
		{-0.5, 0.5, 0.0f,		0,1,0}, //POS2
		{0.5, -0.5, 0.0f,		0,1,0}, //POS3
		{0.5, 0.5, 0.0f,		0,1,0} //POS4
	};
	*/

	m_vb = graphEngine->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2, //FIRST TRIANGLE
		2,3,0, //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	m_ib = graphEngine->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->load(index_list, size_index_list);


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	//Vertex Shader
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = graphEngine->createVertexShader(shader_byte_code, size_shader);

	m_vb->load(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader();

	//Pixel Shader
	graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = graphEngine->createPixelShader(shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader();


	constant cc;
	cc.m_time = 0;

	m_cb = graphEngine->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void AppWindow::onCreate()
{

}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	//CLEAR RENDER TARGET
	graphEngine->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	graphEngine->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);


	updateQuadPosition();


	graphEngine->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	graphEngine->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);


	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	graphEngine->getImmediateDeviceContext()->setVertexShader(m_vs);
	graphEngine->getImmediateDeviceContext()->setPixelShader(m_ps);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	graphEngine->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	//SET THE INIDICES OF THE TRIANGLE TO DRAW
	graphEngine->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	//FINALLY DRAW THE TRIANGLE
	graphEngine->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
	m_swap_chain->present(true);


	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();
	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	m_vb->release();
	m_ib->release();
	m_cb->release();
	m_vs->release();
	m_ps->release();
	graphEngine->release();
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
		m_rot_x += 3.14f * m_delta_time;
	}
	else if (key == 'S')
	{
		m_rot_x -= 3.14f * m_delta_time;
	}
	if (key == 'A')
	{
		m_rot_y += 3.14f * m_delta_time;
	}
	else if (key == 'D')
	{
		m_rot_y -= 3.14f * m_delta_time;
	}
}

void AppWindow::onKeyUp(int key)
{

}

void AppWindow::onMouseMove(const Point& delta_mouse_pos)
{
	m_rot_x -= delta_mouse_pos.m_y * m_delta_time;
	m_rot_y -= delta_mouse_pos.m_x * m_delta_time;
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
