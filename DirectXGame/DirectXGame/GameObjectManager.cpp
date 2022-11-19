#include "GameObjectManager.h"
#include "MathUtils.h"

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager();
	sharedInstance->init();
}

void GameObjectManager::destroy()
{
	if (sharedInstance != NULL)
	{
		sharedInstance->release();
	}
}

void GameObjectManager::init()
{
}

void GameObjectManager::update(int width, int height)
{
	float deltaTime = EngineTime::getDeltaTime();

	for (auto obj : this->object_list)
	{
		obj->update(deltaTime);
		obj->draw(width, height);
	}
}

void GameObjectManager::release()
{
	for (auto obj : this->object_list)
		obj->~AGameObject();
}

AGameObject* GameObjectManager::create(std::string name, PrimitiveType primType, bool canUpdate, Texture* texture)
{
	AGameObject* obj = nullptr;

	if (primType == TRIANGLE)
	{

	}
	else if (primType == QUAD)
	{
		obj = new Quad(name);
		std::cout << "Quad created!" << std::endl;
	}
	else if (primType == CUBE)
	{
		obj = new Cube(name, texture, NULL);
		std::cout << "Cube created!" << std::endl;
	}
	else if (primType == CIRCLE)
	{
		obj = new Circle(name);
		std::cout << "Circle created!" << std::endl;
	}
	else if (primType == PLANE)
	{
		obj = new Plane(name, texture);
		std::cout << "Plane created!" << std::endl;
	}

	this->object_list.push_back(obj);
	obj->canUpdate = canUpdate;

	return obj;
}

AGameObject* GameObjectManager::createMeshObject(std::string name, bool canUpdate, Texture* texture, Mesh* mesh)
{
	AGameObject* obj = nullptr;

	obj = new Cube(name, texture, mesh);
	this->object_list.push_back(obj);
	std::cout << "Mesh Object created!" << std::endl;

	obj->canUpdate = canUpdate;

	return obj;
}

AGameObject* GameObjectManager::createWithTransform(std::string name, PrimitiveType primType, Vector3D transform, TransformType transformType, bool canUpdate)
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

void GameObjectManager::createMultipleRandom(std::string name, PrimitiveType primType, bool canUpdate, int count)
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
			this->object_list.back()->setAnimSpeed(MathUtils::randomFloat(-3.75, 3.75));
			this->object_list.back()->setPosition(x, y, z);
			this->object_list.back()->setScale(0.25f, 0.25f, 0.25f);
		}
		else if (primType == CUBE)
		{
			this->object_list.back()->setAnimSpeed(MathUtils::randomFloat(-3.75, 3.75));
			this->object_list.back()->setPosition(x, y, z);
			this->object_list.back()->setScale(0.25f, 0.25f, 0.25f);
		}
		else if (primType == CIRCLE)
		{
			this->object_list.back()->setAnimSpeed(MathUtils::randomFloat(-3.75, 3.75));
			this->object_list.back()->setPosition(x, y, z);
			this->object_list.back()->setScale(0.25f, 0.25f, 0.25f);
		}
		else if (primType == PLANE)
		{
			this->object_list.back()->setAnimSpeed(MathUtils::randomFloat(-3.75, 3.75));
			this->object_list.back()->setPosition(x, y, z);
			this->object_list.back()->setScale(0.25f, 0.25f, 0.25f);
		}

		
	}
}



