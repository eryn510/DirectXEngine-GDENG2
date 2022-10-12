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
	UINT size_list = ARRAYSIZE(this->vertex_list);
	this->m_vb = m_system->createVertexBuffer(this->vertex_list, sizeof(vertex), size_list, this->shader_byte_code, size_shader);

	//Index Buffer Creation
	UINT size_index_list = ARRAYSIZE(index_list);
	this->m_ib = m_system->createIndexBuffer(index_list, size_index_list);

	//Constant Buffer Creation
	constant cc;
	cc.m_time = 0;
	this->m_cb = m_system->createConstantBuffer(&cc, sizeof(constant));
}

void Cube::update()
{

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	m_system->getImmediateDeviceContext()->setVertexBuffer(this->m_vb);

	//SET THE INDICES OF THE TRIANGLE TO DRAW
	m_system->getImmediateDeviceContext()->setIndexBuffer(this->m_ib);

	//FINALLY DRAW THE TRIANGLE
	m_system->getImmediateDeviceContext()->drawIndexedTriangleList(this->m_ib->getSizeIndexList(), 0, 0);
}

void Cube::release()
{
	delete m_cb;
	delete m_ib;
	delete m_vb;
}

void Cube::setAnimSpeed(float deltaTime)
{
}
