#pragma once
#include <list>
#include "Cube.h"
#include "Quad.h"
#include "Circle.h"

enum PrimitiveType
{
	TRIANGLE = 0,
	QUAD,
	CUBE,
	CIRCLE
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
	void update();
	void release();

	void create(float radius, Vector3D centerVertex, vertex vertex_list[], void* shader_byte_code, size_t size_shader, PrimitiveType primType);

private:
	std::list<Cube*> cube_list;
	std::list<Quad*> quad_list;
	std::list<Circle*> circle_list;

private:
	friend class AppWindow;
};

