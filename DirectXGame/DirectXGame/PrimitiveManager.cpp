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

void PrimitiveManager::update(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	for (auto cube : this->cube_list)
	{
		cube->update(EngineTime::getDeltaTime());
		cube->draw(width, height, vertexShader, pixelShader);
	}

	for (auto quad : this->quad_list)
	{
		quad->update(EngineTime::getDeltaTime());
		quad->draw(width, height, vertexShader, pixelShader);
	}

	for (auto circle : this->circle_list)
	{
		circle->update(EngineTime::getDeltaTime());
		circle->draw(width, height, vertexShader, pixelShader);
	}

	for (auto plane : this->plane_list)
	{
		plane->update(EngineTime::getDeltaTime());
		plane->draw(width, height, vertexShader, pixelShader);
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

void PrimitiveManager::create(std::string name, void* shader_byte_code, size_t size_shader, PrimitiveType primType)
{
	if (primType == TRIANGLE) 
	{

	}
	else if (primType == QUAD) 
	{
		Quad* quad = new Quad(name, shader_byte_code, size_shader);
		this->quad_list.push_back(quad);
	}
	else if (primType == CUBE) 
	{
		Cube* cube = new Cube(name, shader_byte_code, size_shader);
		this->cube_list.push_back(cube);
		std::cout << "Cube created!" << std::endl;
	}
	else if (primType == CIRCLE)
	{
		Circle* circle = new Circle(name, shader_byte_code, size_shader);
		this->circle_list.push_back(circle);
		std::cout << "Circle created!" << std::endl;
	}
	else if (primType == PLANE)
	{
		Plane* plane = new Plane(name, shader_byte_code, size_shader);
		this->plane_list.push_back(plane);
		std::cout << "Plane created!" << std::endl;
	}
		
}



