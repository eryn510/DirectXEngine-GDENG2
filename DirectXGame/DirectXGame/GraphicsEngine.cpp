#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include <exception>

GraphicsEngine* GraphicsEngine::sharedInstance = NULL;

GraphicsEngine::GraphicsEngine()
{
}

bool GraphicsEngine::init()
{
	m_render_system = new RenderSystem();
	m_render_system->init();
	
	m_tex_manager = new TextureManager();

	return true;
}

bool GraphicsEngine::release()
{
	delete m_tex_manager;
	m_render_system->release();
	delete m_render_system;
	return true;
}

GraphicsEngine* GraphicsEngine::getInstance()
{
	return sharedInstance;
}

void GraphicsEngine::initialize()
{
	sharedInstance = new GraphicsEngine();
	sharedInstance->init();
}

void GraphicsEngine::destroy()
{
	if (sharedInstance != NULL)
	{
		sharedInstance->release();
	}
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return m_render_system;
}

TextureManager* GraphicsEngine::getTextureManager()
{
	return m_tex_manager;
}

GraphicsEngine::~GraphicsEngine()
{
}



