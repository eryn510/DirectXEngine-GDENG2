#include "CreditsScreen.h"

CreditsScreen::CreditsScreen(std::string name) : AUIScreen(name)
{
	this->isActive = true;
}

CreditsScreen::~CreditsScreen()
{
}

void CreditsScreen::drawUI()
{
	ImGui::Begin("Credits");
	ImGui::Text("DirectX11 Engine created by :");
	ImGui::Text("		Eryn Tallador");
	ImGui::Text("Special Regards to:");
	ImGui::Text("		Sir Neil De Gallego");
	ImGui::Text("		PardCode");

	if (ImGui::Button("Close"))
		this->isActive = false;

	ImGui::End();
}
