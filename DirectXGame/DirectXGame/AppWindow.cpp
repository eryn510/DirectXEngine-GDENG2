#include "AppWindow.h"
#include <Windows.h>
#include "InputSystem.h"

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

void AppWindow::update()
{
	m_delta_time = EngineTime::getDeltaTime();

	m_anim_time += m_delta_time;

	//m_anim_speed = ((sin(m_anim_time / 2.0) * 8.0f) + 8.0f);

	m_elapsed_time += 1000.0f * m_delta_time * m_anim_speed;


	constant cc;
	cc.m_time = m_elapsed_time;

	m_delta_pos += m_delta_time;

	m_delta_scale += m_delta_time / 0.55f;

	//std::cout << (sin(m_anim_time) + 1.0f) << std::endl;

	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;


	Matrix4x4 temp;

	
	//NO INPUT
	//cc.m_world.setTranslation(Vector3D::lerp(Vector3D(-2, -2, 0), Vector3D(2, 2, 0), m_delta_pos));

	/*
	m_delta_scale += EngineTime::getDeltaTime();

	cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5f, 0.5f, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));

	temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), m_delta_pos));

	cc.m_world *= temp;


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
	
	*/

	//cc.m_world.setTranslation(Vector3D(0.0f, 0.0f, 0.0f));

	if (this->isPerspective) 
	{
		cc.m_world.setIdentity();

		Matrix4x4 world_cam;
		world_cam.setIdentity();

		temp.setIdentity();
		temp.setRotationX(m_rot_x);
		world_cam *= temp;

		temp.setIdentity();
		temp.setRotationY(m_rot_y);
		world_cam *= temp;


		Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.3f);

		new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.3f);

		world_cam.setTranslation(new_pos);

		m_world_cam = world_cam;

		world_cam.inverse();

		cc.m_view = world_cam;

		int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
		int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

		cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);
	}

	else 
	{
		cc.m_world.setScale(Vector3D(1, 1, 1));

		temp.setIdentity();
		temp.setRotationZ(m_delta_scale);
		cc.m_world *= temp;

		temp.setIdentity();
		temp.setRotationY(m_delta_scale);
		cc.m_world *= temp;

		temp.setIdentity();
		temp.setRotationX(m_delta_scale);
		cc.m_world *= temp;

		cc.m_world.setIdentity();
		cc.m_view.setIdentity();
		cc.m_proj.setOrthoLH
		(
			(this->getClientWindowRect().right - this->getClientWindowRect().left) / 300.0f,
			(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 300.0f,
			-4.0f,
			4.0f
		);
	}


	/*
	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left) / 300.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 300.0f,
		-4.0f,
		4.0f
	);
	*/

	///*
	
	//*/

	for (auto cube : primMngr->cube_list)
		cube->m_cb->update(m_render_system->getImmediateDeviceContext(), &cc);

	for (auto quad : primMngr->quad_list)
		quad->m_cb->update(m_render_system->getImmediateDeviceContext(), &cc);

	for (auto circle : primMngr->circle_list)
		circle->m_cb->update(m_render_system->getImmediateDeviceContext(), &cc);
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

	this->isPerspective = true;

	m_swap_chain = m_render_system->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	m_world_cam.setTranslation(Vector3D(0.0f, 0.0f, -2.0f));

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	//Vertex Shader
	m_render_system->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = m_render_system->createVertexShader(shader_byte_code, size_shader);



	
	vertex vertex_list[]
	{
		//	X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f, -0.5f, -0.5f),	Vector3D(-0.5f, -0.5f, -0.5f),	Vector3D(1,0,0),    Vector3D(0.2f,0,0)}, //POS1
		{Vector3D(-0.5f, 0.5f, -0.5f),	Vector3D(-0.5f, 0.5f, -0.5f),	Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0)}, //POS2
		{Vector3D(0.5f, 0.5f, -0.5f),	Vector3D(0.5f, 0.5f, -0.5f),	Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0)}, //POS3
		{Vector3D(0.5f, -0.5f, -0.5f),	Vector3D(0.5f, -0.5f, -0.5f),	Vector3D(1,0,0),    Vector3D(0.2f,0,0)}, //POS4

		//BACK FACE
		{Vector3D(0.5f, -0.5f, 0.5f),	Vector3D(0.5f, -0.5f, 0.5f),	Vector3D(0,1,0),    Vector3D(0,0.2f,0)}, //POS5
		{Vector3D(0.5f, 0.5f, 0.5f),	Vector3D(0.5f, 0.5f, 0.5f),	Vector3D(0,1,1),    Vector3D(0,0.2f,0.2f)}, //POS6
		{Vector3D(-0.5f, 0.5f, 0.5f),	Vector3D(-0.5f, 0.5f, 0.5f),	Vector3D(0,1,1),    Vector3D(0,0.2f,0.2f)}, //POS7
		{Vector3D(-0.5f, -0.5f, 0.5f),	Vector3D(-0.5f, -0.5f, 0.5f),	Vector3D(0,1,0),    Vector3D(0,0.2f,0)} //POS8
	};

	vertex vertex_list1[]
	{
		//	X - Y - Z
		//FRONT FACE
		{Vector3D(-1.0f, -1.0f, -1.0f),	Vector3D(-1.0f, -1.0f, -1.0f),	Vector3D(1,0,0),    Vector3D(0.2f,0,0)}, //POS1
		{Vector3D(-1.0f, -0.5f, -1.0f),	Vector3D(-1.0f, -0.5f, -1.0f),	Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0)}, //POS2
		{Vector3D(-0.5f, -0.5f, -1.0f),	Vector3D(-0.5f, -0.5f, -1.0f),	Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0)}, //POS3
		{Vector3D(-0.5f, -1.0f, -1.0f),	Vector3D(-0.5f, -1.0f, -1.0f),	Vector3D(1,0,0),    Vector3D(0.2f,0,0)}, //POS4

		//BACK FACE
		{Vector3D(-0.5f, -1.0f, -0.5f),	Vector3D(-0.5f, -1.0f, -0.5f),	Vector3D(0,1,0),    Vector3D(0,0.2f,0)}, //POS5
		{Vector3D(-0.5f, -0.5f, -0.5f),	Vector3D(-0.5f, -0.5f, -0.5f),	Vector3D(0,1,1),    Vector3D(0,0.2f,0.2f)}, //POS6
		{Vector3D(-1.0f, -0.5f, -0.5f),	Vector3D(-1.0f, -0.5f, -0.5f),	Vector3D(0,1,1),    Vector3D(0,0.2f,0.2f)}, //POS7
		{Vector3D(-1.0f, -1.0f, -0.5f),	Vector3D(-1.0f, -1.0f, -0.5f),	Vector3D(0,1,0),    Vector3D(0,0.2f,0)} //POS8
	};

	vertex vertex_list2[]
	{
		//	X - Y - Z
		//FRONT FACE
		{Vector3D(1.0f, 1.0f, 1.0f),  Vector3D(1.0f, 1.0f, 1.0f),		Vector3D(1,0,0),    Vector3D(0.2f,0,0)}, //POS1
		{Vector3D(1.0f, 0.5f, 1.0f),  Vector3D(1.0f, 0.5f, 1.0f),		Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0)}, //POS2
		{Vector3D(0.5f, 0.5f, 1.0f),  Vector3D(0.5f, 0.5f, 1.0f),		Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0)}, //POS3
		{Vector3D(0.5f, 1.0f, 1.0f),  Vector3D(0.5f, 1.0f, 1.0f),		Vector3D(1,0,0),    Vector3D(0.2f,0,0)}, //POS4

		//BACK FACE
		{Vector3D(0.5f, 1.0f, 0.5f),  Vector3D(0.5f, 1.0f, 0.5f),		Vector3D(0,1,0),    Vector3D(0,0.2f,0)}, //POS5
		{Vector3D(0.5f, 0.5f, 0.5f),  Vector3D(0.5f, 0.5f, 0.5f),		Vector3D(0,1,1),    Vector3D(0,0.2f,0.2f)}, //POS6
		{Vector3D(1.0f, 0.5f, 0.5f),  Vector3D(1.0f, 0.5f, 0.5f),		Vector3D(0,1,1),    Vector3D(0,0.2f,0.2f)}, //POS7
		{Vector3D(1.0f, 1.0f, 0.5f),  Vector3D(1.0f, 1.0f, 0.5f),		Vector3D(0,1,0),    Vector3D(0,0.2f,0)} //POS8
	};
	
	primMngr->create(0, Vector3D(0, 0, 0), vertex_list, shader_byte_code, size_shader, CUBE);
	primMngr->create(0, Vector3D(0, 0, 0), vertex_list1, shader_byte_code, size_shader, CUBE);
	primMngr->create(0, Vector3D(0, 0, 0), vertex_list2, shader_byte_code, size_shader, CUBE);
	

	vertex vertex_list3[]
	{
		//	X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f, -0.5f, 0.0f),  Vector3D(-0.5f, -0.5f, 0.0f),		Vector3D(1,0,0),    Vector3D(0.2f,0,0)}, //POS1
		{Vector3D(-0.5f, 0.5f, 0.0f),	Vector3D(-0.5f, 0.5f, 0.0f),	Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0)}, //POS2
		{Vector3D(0.5f, 0.5f, 0.0f),	Vector3D(0.5f, 0.5f, 0.0f),	Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0)}, //POS3
		{Vector3D(0.5f, -0.5f, 0.0f),	Vector3D(0.5f, -0.5f, 0.0f),	Vector3D(1,0,0),    Vector3D(0.2f,0,0)}, //POS4
	};

	vertex vertex_list4[]
	{
		//	X - Y - Z
		//FRONT FACE
		{Vector3D(-1.0f, -1.0f, 0.0f),	Vector3D(-1.0f, -1.0f, 0.0f),	Vector3D(1,0,0),    Vector3D(0.2f,0,0)}, //POS1
		{Vector3D(-1.0f, -0.5f, 0.0f),	Vector3D(-1.0f, -0.5f, 0.0f),	Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0)}, //POS2
		{Vector3D(-0.5f, -0.5f, 0.0f),	Vector3D(-0.5f, -0.5f, 0.0f),	Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0)}, //POS3
		{Vector3D(-0.5f, -1.0f, 0.0f),	Vector3D(-0.5f, -1.0f, 0.0f),	Vector3D(1,0,0),    Vector3D(0.2f,0,0)}, //POS4
	};

	vertex vertex_list5[]
	{
		//	X - Y - Z
		//FRONT FACE
		{Vector3D(1.0f, 1.0f, 0.0f),  Vector3D(1.0f, 1.0f, 0.0f),		Vector3D(1,0,0),    Vector3D(0.2f,0,0)}, //POS1
		{Vector3D(1.0f, 0.5f, 0.0f),  Vector3D(1.0f, 0.5f, 0.0f),		Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0)}, //POS2
		{Vector3D(0.5f, 0.5f, 0.0f),  Vector3D(0.5f, 0.5f, 0.0f),		Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0)}, //POS3
		{Vector3D(0.5f, 1.0f, 0.0f),  Vector3D(0.5f, 1.0f, 0.0f),		Vector3D(1,0,0),    Vector3D(0.2f,0,0)}, //POS4
	};

	primMngr->create(0, Vector3D(0, 0, 0), vertex_list3, shader_byte_code, size_shader, QUAD);
	primMngr->create(0, Vector3D(0, 0, 0), vertex_list4, shader_byte_code, size_shader, QUAD);
	primMngr->create(0, Vector3D(0, 0, 0), vertex_list5, shader_byte_code, size_shader, QUAD);
	

	/*
	vertex vertex_list6[]
	{
		//	X - Y - Z
		//FRONT FACE
		{Vector3D(-0.8f, -0.8f, 0.0f), Vector3D(-0.32f,-0.11f,0.0f),	Vector3D(1,0,0),    Vector3D(0,1,1)}, //POS1
		{Vector3D(-0.9f, 0.1f, 0.0f),	Vector3D(-0.11f,0.78f,0.0f),	Vector3D(1,0,0),    Vector3D(1,1,0)}, //POS2
		{Vector3D(0.0f, -0.4f, 0.0f),	Vector3D(0.75f,-0.73f,0.0f),	Vector3D(0,0,1),    Vector3D(1,0,0)}, //POS3
		{Vector3D(0.0f, 0.1f, 0.0f),	Vector3D(0.88f,0.77f,0.0f),		Vector3D(1,1,1),    Vector3D(0,1,0)}, //POS4
	};

	vertex vertex_list7[]
	{
		//	X - Y - Z
		//FRONT FACE
		{Vector3D(-0.8f, -0.95f, 0.0f), Vector3D(-0.32f,-0.05f,0.0f),	Vector3D(1,0,0),    Vector3D(0,1,1)}, //POS1
		{Vector3D(-0.9f, 0.15f, 0.0f),	Vector3D(0.0f,1.0f,0.0f),		Vector3D(1,0,0),    Vector3D(1,1,0)}, //POS2
		{Vector3D(1.0f, -0.4f, 0.0f),	Vector3D(0.0f,-0.9f,0.0f),		Vector3D(0,0,1),    Vector3D(1,0,0)}, //POS3
		{Vector3D(-0.8f, -0.8f, 0.0f),	Vector3D(0.88f,0.77f,0.0f),		Vector3D(1,1,1),    Vector3D(0,1,0)}, //POS4
	};

	primMngr->create(vertex_list7, shader_byte_code, size_shader, QUAD);
	*/
	
	primMngr->create(1, Vector3D(0, 0, 0), nullptr, shader_byte_code, size_shader, CIRCLE);
	
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

	//CLEAR RENDER TARGET
	m_render_system->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	m_render_system->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);


	update();

	for (auto cube : primMngr->cube_list)
	{
		m_render_system->getImmediateDeviceContext()->setConstantBuffer(m_vs, cube->m_cb);
		m_render_system->getImmediateDeviceContext()->setConstantBuffer(m_ps, cube->m_cb);
	}

	for (auto quad : primMngr->quad_list)
	{
		m_render_system->getImmediateDeviceContext()->setConstantBuffer(m_vs, quad->m_cb);
		m_render_system->getImmediateDeviceContext()->setConstantBuffer(m_ps, quad->m_cb);
	}

	for (auto circle : primMngr->circle_list)
	{
		m_render_system->getImmediateDeviceContext()->setConstantBuffer(m_vs, circle->m_cb);
		m_render_system->getImmediateDeviceContext()->setConstantBuffer(m_ps, circle->m_cb);
	}


	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	m_render_system->getImmediateDeviceContext()->setVertexShader(m_vs);
	m_render_system->getImmediateDeviceContext()->setPixelShader(m_ps);

	for (auto cube : primMngr->cube_list)
		cube->update();

	for (auto quad : primMngr->quad_list)
		quad->update();

	for (auto circle : primMngr->circle_list)
		circle->update();
	
	m_swap_chain->present(true);

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
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
	else if (key == VK_LSHIFT) 
	{
		this->isPerspective = !this->isPerspective;
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

	InputSystem::get()->setCursorPosition(Point(width / 2.0f, height / 2.0f));
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
