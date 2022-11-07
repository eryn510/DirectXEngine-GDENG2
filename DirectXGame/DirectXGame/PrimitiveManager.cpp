#include "PrimitiveManager.h"
#include "MathUtils.h"

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
	float deltaTime = EngineTime::getDeltaTime();

	for (auto cube : this->cube_list)
	{
		cube->update(deltaTime);
		cube->draw(width, height);
	}

	for (auto quad : this->quad_list)
	{
		quad->update(deltaTime);
		quad->draw(width, height);
	}

	for (auto circle : this->circle_list)
	{
		circle->update(deltaTime);
		circle->draw(width, height);
	}

	for (auto plane : this->plane_list)
	{
		plane->update(deltaTime);
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

AGameObject* PrimitiveManager::create(std::string name, PrimitiveType primType, bool canUpdate)
{
	AGameObject* primitive = nullptr;

	if (primType == TRIANGLE)
	{

	}
	else if (primType == QUAD)
	{
		Quad* quad = new Quad(name);
		this->quad_list.push_back(quad);
		std::cout << "Quad created!" << std::endl;
		primitive = quad;
	}
	else if (primType == CUBE)
	{
		Cube* cube = new Cube(name);
		this->cube_list.push_back(cube);
		std::cout << "Cube created!" << std::endl;
		primitive = cube;
	}
	else if (primType == CIRCLE)
	{
		Circle* circle = new Circle(name);
		this->circle_list.push_back(circle);
		std::cout << "Circle created!" << std::endl;
		primitive = circle;
	}
	else if (primType == PLANE)
	{
		Plane* plane = new Plane(name);
		this->plane_list.push_back(plane);
		std::cout << "Plane created!" << std::endl;
		primitive = plane;
	}

	primitive->canUpdate = canUpdate;

	return primitive;
}

AGameObject* PrimitiveManager::createWithTransform(std::string name, PrimitiveType primType, Vector3D transform, TransformType transformType, bool canUpdate)
{
	AGameObject* primitive = create(name, primType, canUpdate);

	if (transformType == TRANSLATION)
		primitive->setPosition(transform);
	else if (transformType == ROTATION)
		primitive->setRotation(transform);
	else if (transformType == SCALE)
		primitive->setScale(transform);

	return primitive;
}

void PrimitiveManager::createMultipleRandom(std::string name, PrimitiveType primType, bool canUpdate, int count)
{
	for (int i = 0; i < count; i++) {
		float x = MathUtils::randomFloat(-0.75, 0.75);
		float y = MathUtils::randomFloat(-0.75, 0.75);
		float z = MathUtils::randomFloat(-0.75, 0.75);


		create(name, primType, canUpdate);

		if (primType == TRIANGLE)
		{

		}
		else if (primType == QUAD)
		{
			this->quad_list.back()->setAnimSpeed(MathUtils::randomFloat(-3.75, 3.75));
			this->quad_list.back()->setPosition(x, y, z);
			this->quad_list.back()->setScale(0.25f, 0.25f, 0.25f);
		}
		else if (primType == CUBE)
		{
			this->cube_list.back()->setAnimSpeed(MathUtils::randomFloat(-3.75, 3.75));
			this->cube_list.back()->setPosition(x, y, z);
			this->cube_list.back()->setScale(0.25f, 0.25f, 0.25f);
		}
		else if (primType == CIRCLE)
		{
			this->circle_list.back()->setAnimSpeed(MathUtils::randomFloat(-3.75, 3.75));
			this->circle_list.back()->setPosition(x, y, z);
			this->circle_list.back()->setScale(0.25f, 0.25f, 0.25f);
		}
		else if (primType == PLANE)
		{
			this->plane_list.back()->setAnimSpeed(MathUtils::randomFloat(-3.75, 3.75));
			this->plane_list.back()->setPosition(x, y, z);
			this->plane_list.back()->setScale(0.25f, 0.25f, 0.25f);
		}

		
	}
}



