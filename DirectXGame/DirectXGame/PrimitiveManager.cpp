#include "PrimitiveManager.h"

PrimitiveManager* PrimitiveManager::sharedInstance = NULL;

PrimitiveManager::PrimitiveManager()
{
}

PrimitiveManager::~PrimitiveManager()
{
}

PrimitiveManager* PrimitiveManager::getInstance()
{
	return sharedInstance;
}

void PrimitiveManager::initialize()
{
	sharedInstance = new PrimitiveManager();
	sharedInstance->init();
}

void PrimitiveManager::destroy()
{
	if (sharedInstance != NULL)
	{
		sharedInstance->release();
	}
}

void PrimitiveManager::init()
{
}

void PrimitiveManager::update()
{
}

void PrimitiveManager::release()
{
	for (auto cube : this->cube_list)
		cube->release();
}

void PrimitiveManager::createCube(vertex vertex_list[], void* shader_byte_code, size_t size_shader)
{
	Cube *cube = new Cube(vertex_list, shader_byte_code, size_shader);
	cube->create();
	this->cube_list.push_back(cube);
}



