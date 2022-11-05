#pragma once
#include "AUIScreen.h"

class CreditsScreen : public AUIScreen
{
public:

	CreditsScreen(std::string name);
	~CreditsScreen();
	// Inherited via AUIScreen
	virtual void drawUI() override;
};

