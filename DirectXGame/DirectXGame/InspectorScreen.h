#pragma once
#include "AUIScreen.h"

class InspectorScreen : public AUIScreen
{
public:

	InspectorScreen(std::string name);
	~InspectorScreen();
	// Inherited via AUIScreen
	virtual void drawUI() override;
};