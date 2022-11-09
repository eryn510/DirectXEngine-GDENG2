#pragma once
#include "AUIScreen.h"
class ColorPickerScreen : public AUIScreen
{
public:

	ColorPickerScreen(std::string name);
	~ColorPickerScreen();
	// Inherited via AUIScreen
	virtual void drawUI() override;

private:
	float my_color;
};

