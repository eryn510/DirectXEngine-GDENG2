#pragma once
#include <list>
#include "Cube.h"

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

	void createCube(vertex vertex_list[], void* shader_byte_code, size_t size_shader);

private:
	std::list<Cube*> cube_list;

private:
	friend class AppWindow;
};

