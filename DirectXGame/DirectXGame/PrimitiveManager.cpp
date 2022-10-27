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

void PrimitiveManager::update(int width, int height)
{
	for (auto cube : this->cube_list)
	{
		cube->update(0);
		cube->draw(width, height);
	}

	for (auto quad : this->quad_list)
	{
		quad->update(0);
		quad->draw(width, height);
	}

	for (auto circle : this->circle_list)
	{
		circle->update(0);
		circle->draw(width, height);
	}

	for (auto plane : this->plane_list)
	{
		plane->update(0);
		plane->draw(width, height);
	}
}

void PrimitiveManager::release()
{
	for (auto cube : this->cube_list)
		cube->~Cube();
	for (auto quad : this->quad_list)
		quad->~Quad();
	for (auto circle : this->circle_list)
		circle->~Circle();
	for (auto plane : this->plane_list)
		plane->~Plane();
}

void PrimitiveManager::create(std::string name, PrimitiveType primType)
{
	if (primType == TRIANGLE) 
	{

	}
	else if (primType == QUAD) 
	{
		Quad* quad = new Quad(name);
		this->quad_list.push_back(quad);
	}
	else if (primType == CUBE) 
	{
		Cube* cube = new Cube(name);
		this->cube_list.push_back(cube);
		std::cout << "Cube created!" << std::endl;
	}
	else if (primType == CIRCLE)
	{
		Circle* circle = new Circle(name);
		this->circle_list.push_back(circle);
		std::cout << "Circle created!" << std::endl;
	}
	else if (primType == PLANE)
	{
		Plane* plane = new Plane(name);
		this->plane_list.push_back(plane);
		std::cout << "Plane created!" << std::endl;
	}
		
}



