#include "Cube.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

Cube::Cube(vertex vertex_list[], void* shader_byte_code, size_t size_shader) : AGameObject(shader_byte_code,size_shader)
{
	memcpy(this->vertex_list, vertex_list, sizeof(vertex) * 8);
	this->shader_byte_code = shader_byte_code;
	this->size_shader = size_shader;
	
} 

Cube::~Cube()
{
}


void Cube::create()
{


	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2, //FIRST TRIANGLE
		2,3,0, //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};


	//Vertex Buffer Creation
	this->cube_vb = graphEngine->createVertexBuffer();
	UINT size_list = ARRAYSIZE(this->vertex_list);

	this->cube_vb->load(this->vertex_list, sizeof(vertex), size_list, this->shader_byte_code, size_shader);

	//Index Buffer Creation
	this->cube_ib = graphEngine->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	this->cube_ib->load(index_list, size_index_list);

	constant cc;
	cc.m_time = 0;

	this->cube_cb = graphEngine->createConstantBuffer();
	this->cube_cb->load(&cc, sizeof(constant));
}

void Cube::update()
{

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	graphEngine->getImmediateDeviceContext()->setVertexBuffer(this->cube_vb);

	//SET THE INDICES OF THE TRIANGLE TO DRAW
	graphEngine->getImmediateDeviceContext()->setIndexBuffer(this->cube_ib);

	//FINALLY DRAW THE TRIANGLE
	graphEngine->getImmediateDeviceContext()->drawIndexedTriangleList(this->cube_ib->getSizeIndexList(), 0, 0);
}

void Cube::release()
{
	this->cube_cb->release();
	this->cube_ib->release();
	this->cube_vb->release();
}

void Cube::setAnimSpeed(float deltaTime)
{
}