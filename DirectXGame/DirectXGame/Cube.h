#pragma once
#include "Vector3D.h"
#include "AppWindow.h"
#include "GraphicsEngine.h"

struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

class Cube
{
public:
	Cube(vertex vertex_list[]);
	~Cube();
	
public:
	AppWindow* appInstance = AppWindow::getInstance();
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();

public:
	void createCube();
	vertex m_vertex_list[];
};

