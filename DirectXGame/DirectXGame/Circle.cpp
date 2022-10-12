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
	std::setprecision(3);

	Vector3D vertexPoints[arcCount] = {};
	vertexPoints[0] = this->centerPoint;

	for (int i = 1; i < arcCount; ++i)
	{
		theta = (2 * M_PI / static_cast<float>(arcCount)) * i;
		vertexPoints[i] = { floorf((this->centerPoint.m_x + (cos(theta) * this->radius)) * 100) / 100,
			floorf((this->centerPoint.m_y - (sin(theta) * this->radius)) * 100) / 100, this->centerPoint.m_z};
		//std::cout << "(" << vertexPoints[i].m_x << "," << vertexPoints[i].m_y << ")" << std::endl;
	}

	unsigned int index_list[arcCount * 3] = { };

	int indice2 = 1;
	int indice3 = 2;

	
	for (int i = 0; i < (arcCount * 3) - 3; i += 3)
	{
		index_list[i] = 0;
		index_list[i + 1] = indice2;
		index_list[i + 2] = indice3;
		
		indice2++;
		indice3++;

		std::cout << index_list[i] << "," << index_list[i + 1] << "," << index_list[i + 2] << std::endl;
	}

	index_list[(arcCount * 3) - 3] = 0;
	index_list[(arcCount * 3) - 2] = arcCount - 1;
	index_list[(arcCount * 3) - 1] = 1;


	for (int j = 0; j < arcCount; j++) 
	{
		this->vertex_list[j].position = Vector3D(vertexPoints[j].m_x, vertexPoints[j].m_y, vertexPoints[j].m_z);
		this->vertex_list[j].position1 = Vector3D(vertexPoints[j].m_x, vertexPoints[j].m_y, vertexPoints[j].m_z);
		this->vertex_list[j].color = Vector3D(1, 1, 1);
		this->vertex_list[j].color1 = Vector3D(0, 0, 1);
	}

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

void Circle::update()
{

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	m_system->getImmediateDeviceContext()->setVertexBuffer(this->m_vb);

	//SET THE INDICES OF THE TRIANGLE TO DRAW
	m_system->getImmediateDeviceContext()->setIndexBuffer(this->m_ib);

	//FINALLY DRAW THE TRIANGLE
	//graphEngine->getImmediateDeviceContext()->drawTriangleStrip(this->m_vb->getSizeVertexList(), 0);
	m_system->getImmediateDeviceContext()->drawIndexedTriangleList(this->m_ib->getSizeIndexList(), 0, 0);
}

void Circle::release()
{
	delete m_cb;
	delete m_ib;
	delete m_vb;
	delete this;
}

void Circle::setAnimSpeed(float deltaTime)
{
}