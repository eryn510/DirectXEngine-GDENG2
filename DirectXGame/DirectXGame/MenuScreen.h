#pragma once
#include "AUIScreen.h"

class MenuScreen : public AUIScreen
{
public:

	MenuScreen(std::string name);
	~MenuScreen();
	// Inherited via AUIScreen
	virtual void drawUI() override;

private:
	bool menu_active;
};