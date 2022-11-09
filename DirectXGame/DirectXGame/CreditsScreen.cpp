#include "CreditsScreen.h"
#include "Texture.h"
#include "GraphicsEngine.h"

CreditsScreen::CreditsScreen(std::string name) : AUIScreen(name)
{
	this->isActive = false;
}

CreditsScreen::~CreditsScreen()
{
}

void CreditsScreen::drawUI()
{
	ImGui::Begin("Credits");

	Texture* m_logo = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\logo.jpg");
	ImGui::Image((void*)m_logo->getShaderResourceView(), ImVec2(256, 256));

	ImGui::Text("DirectX11 Engine created by :");
	ImGui::Text("		Eryn Tallador");
	ImGui::Text("Acknowledgements:");
	ImGui::Text("		Sir Neil Del Gallego");
	ImGui::Text("		PardCode : 'https://www.youtube.com/c/PardCode'");
	ImGui::Text("		Jpres : 'https://www.youtube.com/user/Jpres'");
	ImGui::Text("		Emerson Celestial");
	ImGui::Text("		Aldrey Gaurana");

	if (ImGui::Button("Close"))
		this->isActive = false;

	ImGui::End();
}
