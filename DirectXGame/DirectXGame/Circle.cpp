#define _USE_MATH_DEFINES
#include "Circle.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include <cmath>

Circle::Circle(float radius, Vector3D centerVertex, void* shader_byte_code, size_t size_shader) : AGameObject(shader_byte_code, size_shader)
{
	this->radius = radius;
	this->centerPoint = centerVertex;
	this->shader_byte_code = shader_byte_code;
	this->size_shader = size_shader;

}

Circle::~Circle()
{
}


void Circle::create()
{
	float theta;
	float circumference = 2 * M_PI * this->radius;

	Vector3D vertexPoints[arcCount] = {};
	vertexPoints[0] = this->centerPoint;

	for (int i = 1; i < arcCount; ++i)
	{
		theta = (360 / static_cast<float>(arcCount)) * i;
		vertexPoints[i] = { this->centerPoint.m_x + (cos(theta) * this->radius), this->centerPoint.m_y + (sin(theta) * this->radius), this->centerPoint.m_z};
	}

	unsigned int index_list[arcCount * 3] = { };

	int indice2 = 1;
	int indice3 = 2;
	int counter = 0;

	
	for (int i = 0; i < (arcCount * 3) - 3; i += 3)
	{
		index_list[i] = 0;
		counter++;
		index_list[i + 1] = indice2;
		counter++;
		index_list[i + 2] = indice3;
		counter++;

		indice2++;
		indice3++;

		std::cout << index_list[i] << "," << index_list[i + 1] << "," << index_list[i + 2] << "," << counter << std::endl;
	}

	index_list[arcCount - 2] = 0;
	index_list[arcCount - 1] = arcCount;
	index_list[arcCount] = 1;


	for (int j = 0; j < arcCount; j++) 
	{
		this->vertex_list[j].position = Vector3D(vertexPoints[j].m_x, vertexPoints[j].m_y, vertexPoints[j].m_z);
		this->vertex_list[j].position1 = Vector3D(vertexPoints[j].m_x, vertexPoints[j].m_y, vertexPoints[j].m_z);
		this->vertex_list[j].color = Vector3D(1, 1, 1);
		this->vertex_list[j].color1 = Vector3D(0, 0, 1);


		std::cout << "(" << this->vertex_list[j].position.m_x << "," << this->vertex_list[j].position.m_y << ")" << std::endl;
	}

	//std::cout << "(" << this->vertex_list[0].position.m_x << "," << this->vertex_list[0].position.m_y << ")" << std::endl;
	//std::cout << "(" << this->vertex_list[1].position.m_x << "," << this->vertex_list[1].position.m_y << ")" << std::endl;
	//std::cout << "(" << this->vertex_list[2].position.m_x << "," << this->vertex_list[2].position.m_y << ")" << std::endl;

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

void Circle::update()
{

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	graphEngine->getImmediateDeviceContext()->setVertexBuffer(this->m_vb);

	//SET THE INDICES OF THE TRIANGLE TO DRAW
	graphEngine->getImmediateDeviceContext()->setIndexBuffer(this->m_ib);

	//FINALLY DRAW THE TRIANGLE
	//graphEngine->getImmediateDeviceContext()->drawTriangleStrip(this->m_vb->getSizeVertexList(), 0);
	graphEngine->getImmediateDeviceContext()->drawIndexedTriangleList(this->m_ib->getSizeIndexList(), 0, 0);
}

void Circle::release()
{
	this->m_cb->release();
	this->m_ib->release();
	this->m_vb->release();
	delete this;
}

void Circle::setAnimSpeed(float deltaTime)
{
}