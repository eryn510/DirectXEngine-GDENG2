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
	this->m_vb = graphEngine->createVertexBuffer();
	UINT size_list = ARRAYSIZE(this->vertex_list);

	this->m_vb->load(this->vertex_list, sizeof(vertex), size_list, this->shader_byte_code, size_shader);

	//Index Buffer Creation
	this->m_ib = graphEngine->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	this->m_ib->load(index_list, size_index_list);

	constant cc;
	cc.m_time = 0;

	this->m_cb = graphEngine->createConstantBuffer();
	this->m_cb->load(&cc, sizeof(constant));
}

void Quad::update()
{

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	graphEngine->getImmediateDeviceContext()->setVertexBuffer(this->m_vb);

	//SET THE INDICES OF THE TRIANGLE TO DRAW
	graphEngine->getImmediateDeviceContext()->setIndexBuffer(this->m_ib);

	//FINALLY DRAW THE TRIANGLE
	graphEngine->getImmediateDeviceContext()->drawIndexedTriangleList(this->m_ib->getSizeIndexList(), 0, 0);
}

void Quad::release()
{
	this->m_cb->release();
	this->m_ib->release();
	this->m_vb->release();
	delete this;
}

void Quad::setAnimSpeed(float deltaTime)
{
}