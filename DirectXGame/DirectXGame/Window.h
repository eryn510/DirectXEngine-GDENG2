#pragma once
#define NOMINMAX
#include "Windows.h"
#include "EngineTime.h"

class Window
{
public:
	Window();
	//Initialize Window
	bool init();
	bool broadcast();
	bool isRun();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	//Release Window
	bool release();
	~Window();

	//EVENTS
	virtual void onCreate()=0;
	virtual void onUpdate()=0;
	virtual void onDestroy()=0;
	virtual void onFocus() = 0;
	virtual void onKillFocus() = 0;

protected:
	HWND m_hwnd;
	bool m_is_run;
};

