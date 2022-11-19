#pragma once
#include <list>
#include "Cube.h"
#include "Quad.h"
#include "Circle.h"
#include "Plane.h"

enum PrimitiveType
{
	TRIANGLE = 0,
	QUAD,
	CUBE,
	CIRCLE,
	PLANE
};

enum TransformType
{
	TRANSLATION = 0,
	ROTATION,
	SCALE
};

class AppWindow;

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};
	static GameObjectManager* sharedInstance;

public:
	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

public:
	void init();
	void update(int width, int height);
	void release();

	AGameObject* create(std::string name, PrimitiveType primType, bool canUpdate, Texture* texture = NULL);
	AGameObject* createMeshObject(std::string name, bool canUpdate, Texture* texture = NULL, Mesh* mesh = NULL);
	AGameObject* createWithTransform(std::string name, PrimitiveType primType, Vector3D transform, TransformType transformType, bool canUpdate);
	void createMultipleRandom(std::string name, PrimitiveType primType, bool canUpdate, int count);

private:
	std::list<AGameObject*> object_list;

private:
	friend class AppWindow;
	friend class InspectorScreen;
};

