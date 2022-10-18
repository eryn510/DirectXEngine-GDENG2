#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include <exception>

GraphicsEngine* GraphicsEngine::sharedInstance = NULL;

GraphicsEngine::GraphicsEngine()
{
	try 
	{
		m_render_system = new RenderSystem();
	}
	catch (...) { throw std::exception("Graphics Engine not created successfully"); };
}

GraphicsEngine* GraphicsEngine::getInstance()
{
	return sharedInstance;
}

void GraphicsEngine::initialize()
{
	sharedInstance = new GraphicsEngine();
}

void GraphicsEngine::destroy()
{
	if (sharedInstance != NULL)
	{
		sharedInstance->~GraphicsEngine();
	}
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return m_render_system;
}

GraphicsEngine::~GraphicsEngine()
{
	m_render_system->destroy();
	delete m_render_system;
}



