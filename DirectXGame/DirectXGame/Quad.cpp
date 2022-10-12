#include "Quad.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

Quad::Quad(vertex vertex_list[], void* shader_byte_code, size_t size_shader) : AGameObject(shader_byte_code, size_shader)
{
	memcpy(this->vertex_list, vertex_list, sizeof(vertex) * 4);
	this->shader_byte_code = shader_byte_code;
	this->size_shader = size_shader;

}

Quad::~Quad()
{
}


void Quad::create()
{

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2, //FIRST TRIANGLE
		2,3,0, //SECOND TRIANGLE
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

void Quad::update()
{

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	m_system->getImmediateDeviceContext()->setVertexBuffer(this->m_vb);

	//SET THE INDICES OF THE TRIANGLE TO DRAW
	m_system->getImmediateDeviceContext()->setIndexBuffer(this->m_ib);

	//FINALLY DRAW THE TRIANGLE
	//graphEngine->getImmediateDeviceContext()->drawTriangleStrip(this->m_vb->getSizeVertexList(), 0);
	m_system->getImmediateDeviceContext()->drawIndexedTriangleList(this->m_ib->getSizeIndexList(), 0, 0);
}

void Quad::release()
{
	delete m_cb;
	delete m_ib;
	delete m_vb;
	delete this;
}

void Quad::setAnimSpeed(float deltaTime)
{
}