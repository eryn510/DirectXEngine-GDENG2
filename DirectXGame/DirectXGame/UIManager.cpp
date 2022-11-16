#include "UIManager.h"
#include "GraphicsEngine.h"
#include "RenderSystem.h"

UIManager* UIManager::sharedInstance = NULL;

UIManager* UIManager::getInstance()
{
	return sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{
	sharedInstance = new UIManager(windowHandle);
}

void UIManager::destroy()
{
	delete sharedInstance;
}

void UIManager::drawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (int i = 0; i < this->uiList.size(); i++) 
	{
		if (this->uiList[i]->isActive == true)
			this->uiList[i]->drawUI();
	}

	//ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIManager::UIManager(HWND windowHandle)
{
	RenderSystem* m_system = GraphicsEngine::getInstance()->getRenderSystem();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); 
	(void)io;

	ImGui::StyleColorsDark;

	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(m_system->getDevice(), m_system->getDeviceContext());

	UINames uiNames;

	MenuScreen* menuScreen = new MenuScreen("Menu");
	this->uiTable[uiNames.MENU_SCREEN] = menuScreen;
	this->uiList.push_back(menuScreen);

	CreditsScreen* creditsScreen = new CreditsScreen("Credits");
	this->uiTable[uiNames.CREDITS_SCREEN] = creditsScreen;
	this->uiList.push_back(creditsScreen);

	ColorPickerScreen* colorPickerScreen = new ColorPickerScreen("Color Picker");
	this->uiTable[uiNames.COLORPICKER_SCREEN] = colorPickerScreen;
	this->uiList.push_back(colorPickerScreen);

	InspectorScreen* inspectorScreen = new InspectorScreen("Inspector Screen");
	this->uiTable[uiNames.INSPECTOR_SCREEN] = inspectorScreen;
	this->uiList.push_back(inspectorScreen);
}

UIManager::~UIManager()
{

}
