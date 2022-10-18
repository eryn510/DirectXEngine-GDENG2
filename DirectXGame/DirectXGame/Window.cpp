#include "Window.h"
#include <exception>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
switch (msg)
{
case WM_CREATE:
{

	break;
}
case WM_SETFOCUS:
{
	//Event for Window Focus
	Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	//THIS SNIPPET OF CODE WILL RECOVER THE POINTER "THIS" FROM THE SPECIAL STRUCTURE DATA IDENTIFIED BY HWND
	if (window) window->onFocus();
	break;
}
case WM_KILLFOCUS:
{
	//Event for Window Lost Focus
	Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	//THIS SNIPPET OF CODE WILL RECOVER THE POINTER "THIS" FROM THE SPECIAL STRUCTURE DATA IDENTIFIED BY HWND
	window->onKillFocus();
	break;
}
case WM_DESTROY:
{
	//Event for Window Destroy
	Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	//THIS SNIPPET OF CODE WILL RECOVER THE POINTER "THIS" FROM THE SPECIAL STRUCTURE DATA IDENTIFIED BY HWND

	window->onDestroy();
	::PostQuitMessage(0);
	break;
}
default:
	return ::DefWindowProc(hwnd, msg, wparam, lparam);
}



}

Window::Window()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = WndProc;

	if (!::RegisterClassEx(&wc))
		throw std::exception("Window not created");

	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectXApplication", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, NULL);

	if (!m_hwnd)
		throw std::exception("Window not created");

	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	m_is_run = true;

	EngineTime::initialize();
}


bool Window::broadcast()
{
	EngineTime::LogFrameStart();
	MSG msg;

	if (!this->m_isInit) 
	{
		//Event for window creation
		SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
		this->onCreate();
		this->m_isInit = true;
	}

	this->onUpdate();

	while(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	Sleep(1);
	EngineTime::LogFrameEnd();

	return true;
}

bool Window::isRun()
{
	if (m_is_run)
		broadcast();
	return m_is_run;
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	return rc;
}

void Window::onCreate()
{
	
}


void Window::onUpdate()
{
	
}

void Window::onDestroy()
{
	m_is_run = false;
}

void Window::onFocus()
{
}

void Window::onKillFocus()
{
}

Window::~Window()
{
	
}
