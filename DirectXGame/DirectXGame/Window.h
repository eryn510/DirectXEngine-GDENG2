#pragma once
#include "Windows.h"
#include "EngineTime.h"

class Window
{
public:
	//Initialize Window
	Window();
	bool isRun();

	RECT getClientWindowRect();

	//Release Window
	~Window();

	//EVENTS
	virtual void onCreate()=0;
	virtual void onUpdate()=0;
	virtual void onDestroy()=0;
	virtual void onFocus() = 0;
	virtual void onKillFocus() = 0;

private:
	bool broadcast();

protected:
	HWND m_hwnd;
	bool m_is_run;
	bool m_isInit;
};

