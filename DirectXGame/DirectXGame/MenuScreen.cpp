#include "MenuScreen.h"
#include "UIManager.h"

MenuScreen::MenuScreen(std::string name) : AUIScreen(name)
{
	this->isActive = true;
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::drawUI()
{
    UINames uiNames;

    ImGui::Begin("Menu", &menu_active, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("About"))
        {
            if (ImGui::MenuItem("Credits", "Ctrl+O")) { UIManager::getInstance()->uiTable[uiNames.CREDITS_SCREEN]->isActive = true; }
            if (ImGui::MenuItem("Color Picker", "Ctrl+S")) { UIManager::getInstance()->uiTable[uiNames.COLORPICKER_SCREEN]->isActive = true; }
            if (ImGui::MenuItem("Close", "Ctrl+W")) { menu_active = false; }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();
}