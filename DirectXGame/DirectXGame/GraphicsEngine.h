#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "RenderSystem.h"
#include "TextureManager.h"

class GraphicsEngine
{
public:
	//initialize graphics engine and DirectX 11 device
	bool init();
	//release resources loaded
	bool release();

public:
	static GraphicsEngine* getInstance();
	static void initialize();
	static void destroy();

public:
	RenderSystem* getRenderSystem();
	TextureManager* getTextureManager();

private:
	GraphicsEngine();
	~GraphicsEngine();
	GraphicsEngine(GraphicsEngine const&) {};
	GraphicsEngine& operator=(GraphicsEngine const&) {};
	static GraphicsEngine* sharedInstance;

private:
	RenderSystem* m_render_system = nullptr;
	TextureManager* m_tex_manager = nullptr;

};

