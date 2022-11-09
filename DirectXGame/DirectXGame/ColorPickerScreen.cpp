#include "ColorPickerScreen.h"

ColorPickerScreen::ColorPickerScreen(std::string name) : AUIScreen(name)
{
    this->isActive = false;
}

ColorPickerScreen::~ColorPickerScreen()
{
}

void ColorPickerScreen::drawUI()
{
	ImGui::Begin("Color");
	ImGui::ColorEdit4("Color", &my_color);

	if (ImGui::Button("Close"))
	{
		this->isActive = false;
	}


	ImGui::End();
}