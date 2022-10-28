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

class PrimitiveManager
{
public:
	PrimitiveManager();
	~PrimitiveManager();
	PrimitiveManager(PrimitiveManager const&) {};
	PrimitiveManager& operator=(PrimitiveManager const&) {};
	static PrimitiveManager* sharedInstance;

public:
	static PrimitiveManager* getInstance();
	static void initialize();
	static void destroy();

public:
	void init();
	void update(int width, int height);
	void release();

	AGameObject* create(std::string name, PrimitiveType primType, bool canUpdate);
	void createWithTransform(std::string name, PrimitiveType primType, Vector3D transform, TransformType transformType, bool canUpdate);
	void createMultipleRandom(std::string name, PrimitiveType primType, bool canUpdate, int count);

private:
	std::list<Cube*> cube_list;
	std::list<Quad*> quad_list;
	std::list<Circle*> circle_list;
	std::list<Plane*> plane_list;

private:
	friend class AppWindow;
};

