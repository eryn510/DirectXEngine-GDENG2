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
	void update(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader);
	void release();

	void create(std::string name, void* shader_byte_code, size_t size_shader, PrimitiveType primType);

private:
	std::list<Cube*> cube_list;
	std::list<Quad*> quad_list;
	std::list<Circle*> circle_list;
	std::list<Plane*> plane_list;

private:
	friend class AppWindow;
};

