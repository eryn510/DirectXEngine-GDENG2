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

void PrimitiveManager::create(float radius, Vector3D centerVertex, vertex vertex_list[], void* shader_byte_code, size_t size_shader, PrimitiveType primType)
{
	if (primType == TRIANGLE) 
	{

	}
	else if (primType == QUAD) 
	{
		Quad* quad = new Quad(vertex_list, shader_byte_code, size_shader);
		quad->create();
		this->quad_list.push_back(quad);
	}
	else if (primType == CUBE) 
	{
		Cube* cube = new Cube(vertex_list, shader_byte_code, size_shader);
		cube->create();
		this->cube_list.push_back(cube);
	}
	else if (primType == CIRCLE)
	{
		Circle* circle = new Circle(radius, centerVertex, shader_byte_code, size_shader);
		circle->create();
		this->circle_list.push_back(circle);
	}
		
}



