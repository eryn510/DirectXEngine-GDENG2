#include "AppWindow.h"

#include "DeviceContext.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 color;
};

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	///*
	//RECTANGLE RAINBOW
	vertex list[]
	{
		//	X - Y - Z	QUAD
		{-0.5, -0.5, 0.0f,		1,0,0}, //POS1
		{-0.5, 0.5, 0.0f,		0,1,0}, //POS2
		{0.5, -0.5, 0.0f,		0,0,1}, //POS3
		{0.5, 0.5, 0.0f,		1,1,0} //POS4
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

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	//Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR RENDER TARGET
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	//FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	m_vb->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}
