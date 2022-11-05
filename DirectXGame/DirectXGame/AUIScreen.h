#pragma once
#include <string>
#include <iostream>
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_win32.h"
#include "IMGUI/imgui_impl_dx11.h"

class UIManager;

class AUIScreen 
{
protected:
	AUIScreen(std::string name) 
	{
		
	};
	~AUIScreen() 
	{

	};

	std::string getName() 
	{
		return this->name;
	};

	std::string name;

public:
	virtual void drawUI() = 0;

	bool isActive = true;

protected:

	friend class UIManager;
};