#define _USE_MATH_DEFINES
#include "Circle.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include <cmath>

Circle::Circle(std::string name, void* shader_byte_code, size_t size_shader) : AGameObject(name)
{
	this->radius = 1;
	this->centerPoint = Vector3D::zeros();

	float theta;
	std::setprecision(3);

	Vector3D vertexPoints[arcCount] = {};
	vertexPoints[0] = this->centerPoint;

	for (int i = 1; i < arcCount; ++i)
	{
		theta = (2 * M_PI / static_cast<float>(arcCount)) * i;
		vertexPoints[i] = { floorf((this->centerPoint.m_x + (cos(theta) * this->radius)) * 100) / 100,
			floorf((this->centerPoint.m_y - (sin(theta) * this->radius)) * 100) / 100, this->centerPoint.m_z };
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

Circle::~Circle()
{

}

void Circle::update(float deltaTime)
{
	
}

void Circle::draw(int width, int height, VertexShaderPtr vertexShader, PixelShaderPtr pixelShader)
{
	DeviceContextPtr deviceContext = m_system->getImmediateDeviceContext();

	constant cc = {};

	/*
	if (this->deltaPos > 1.0f)
		this->deltaPos = 0.0f;
	else
		this->deltaPos += this->deltaTime * 0.1f;
	*/

	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix;
	translationMatrix.setIdentity();
	translationMatrix.setTranslation(this->getLocalPosition());

	Matrix4x4 scaleMatrix;
	scaleMatrix.setIdentity();
	scaleMatrix.setScale(this->getLocalScale());


	Vector3D rotation = this->getLocalRotation();

	Matrix4x4 zMatrix;
	zMatrix.setIdentity();
	zMatrix.setRotationZ(rotation.m_z);

	Matrix4x4 xMatrix;
	xMatrix.setIdentity();
	xMatrix.setRotationX(rotation.m_x);

	Matrix4x4 yMatrix;
	yMatrix.setIdentity();
	yMatrix.setRotationY(rotation.m_y);

	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix * xMatrix * yMatrix * zMatrix;
	allMatrix = allMatrix * scaleMatrix * rotMatrix;
	allMatrix *= translationMatrix;
	cc.m_world = allMatrix;

	//std::cout << allMatrix.m_mat[0][0] << "," << allMatrix.m_mat[1][1] << "," << allMatrix.m_mat[2][2] << std::endl;

	/*
	this->m_world_cam.setTranslation(Vector3D(0.0f, 0.0f, -2.0f));

	Matrix4x4 temp;

	cc.m_world.setIdentity();

	Matrix4x4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(0.0f);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(0.0f);
	world_cam *= temp;


	Vector3D new_pos = this->m_world_cam.getTranslation() + world_cam.getZDirection() * (0.0f * 0.3f);

	new_pos = new_pos + world_cam.getXDirection() * (0.0f * 0.3f);

	world_cam.setTranslation(new_pos);

	this->m_world_cam = world_cam;

	world_cam.inverse();

	cc.m_view = world_cam;

	float aspectRatio = width / height;
	cc.m_proj.setPerspectiveFovLH(aspectRatio, aspectRatio, 0.1f, 1000.0f);
	*/

	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);

	this->deltaTime = EngineTime::getDeltaTime();
	this->elapsedTime += 1000.0f * deltaTime;
	cc.m_time = this->elapsedTime;

	this->m_cb->update(deviceContext, &cc);

	deviceContext->setConstantBuffer(vertexShader, this->m_cb);
	deviceContext->setConstantBuffer(pixelShader, this->m_cb);

	deviceContext->setVertexBuffer(this->m_vb);
	deviceContext->setIndexBuffer(this->m_ib);

	deviceContext->drawIndexedTriangleList(this->m_ib->getSizeIndexList(), 0, 0);
}

void Circle::setAnimSpeed(float multiplier)
{
	this->animSpeed = multiplier;
}