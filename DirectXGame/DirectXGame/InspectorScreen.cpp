#define NOMINMAX
#include <limits>
#include "InspectorScreen.h"

#include "PrimitiveManager.h"
#include "EngineTime.h"

InspectorScreen::InspectorScreen(std::string name) : AUIScreen(name)
{
	this->isActive = true;
}

InspectorScreen::~InspectorScreen()
{
}

typedef float vec3[3];
void InspectorScreen::drawUI()
{
	//DRAW HERE
	ImGui::Begin("Inspector");
	AGameObject* gameObject = PrimitiveManager::getInstance()->cube_list.front();

	if (ImGui::CollapsingHeader("Transform"))
	{
		vec3 pos = { gameObject->getLocalPosition().m_x, gameObject->getLocalPosition().m_y, gameObject->getLocalPosition().m_z };
		vec3 scale = { gameObject->getLocalScale().m_x, gameObject->getLocalScale().m_y, gameObject->getLocalScale().m_z };
		vec3 rot = { gameObject->getLocalRotation().m_x, gameObject->getLocalRotation().m_y, gameObject->getLocalRotation().m_z };

		ImGui::DragFloat3("Position", pos, EngineTime::getDeltaTime(), (float)-std::numeric_limits<int>::max(), (float)std::numeric_limits<int>::max());
		ImGui::DragFloat3("Rotation", rot, EngineTime::getDeltaTime(), (float)-std::numeric_limits<int>::max(), (float)std::numeric_limits<int>::max());
		ImGui::DragFloat3("Scale", scale, EngineTime::getDeltaTime(), (float)-std::numeric_limits<int>::max(), (float)std::numeric_limits<int>::max());

		gameObject->setPosition(pos[0], pos[1], pos[2]);
		gameObject->setRotation(rot[0], rot[1], rot[2]);
		gameObject->setScale(scale[0], scale[1], scale[2]);
	}


	ImGui::End();
}