#include "Plane.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "InputSystem.h"

Plane::Plane(std::string name, void* shader_byte_code, size_t size_shader) : Cube(name, shader_byte_code, size_shader)
{
	vertex quad_list[]
	{
		//	X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f, -0.5f, -0.5f),	Vector3D(-0.5f, -0.5f, -0.5f),	Vector3D(1,1,1),   Vector3D(1,1,1)}, //POS1
		{Vector3D(-0.5f, 0.5f, -0.5f),	Vector3D(-0.5f, 0.5f, -0.5f),	Vector3D(1,1,1),   Vector3D(1,1,1)}, //POS2
		{Vector3D(0.5f, 0.5f, -0.5f),	Vector3D(0.5f, 0.5f, -0.5f),	Vector3D(1,1,1),   Vector3D(1,1,1)}, //POS3
		{Vector3D(0.5f, -0.5f, -0.5f),	Vector3D(0.5f, -0.5f, -0.5f),	Vector3D(1,1,1),   Vector3D(1,1,1)}, //POS4

		//BACK FACE
		{Vector3D(0.5f, -0.5f, 0.5f),	Vector3D(0.5f, -0.5f, 0.5f),	Vector3D(1,1,1),   Vector3D(1,1,1)}, //POS5
		{Vector3D(0.5f, 0.5f, 0.5f),	Vector3D(0.5f, 0.5f, 0.5f),		Vector3D(1,1,1),   Vector3D(1,1,1)}, //POS6
		{Vector3D(-0.5f, 0.5f, 0.5f),	Vector3D(-0.5f, 0.5f, 0.5f),	Vector3D(1,1,1),   Vector3D(1,1,1)}, //POS7
		{Vector3D(-0.5f, -0.5f, 0.5f),	Vector3D(-0.5f, -0.5f, 0.5f),	Vector3D(1,1,1),   Vector3D(1,1,1)} //POS8
	};

	//Vertex Buffer Creation
	UINT size_list = ARRAYSIZE(quad_list);
	this->m_vb = m_system->createVertexBuffer(quad_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

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

	//Index Buffer Creation
	UINT size_index_list = ARRAYSIZE(index_list);
	this->m_ib = m_system->createIndexBuffer(index_list, size_index_list);

	//Constant Buffer Creation
	constant cc;
	cc.m_time = 0;
	this->m_cb = m_system->createConstantBuffer(&cc, sizeof(constant));

	this->setScale(8.0f, 0.1f, 8.0f);
	this->setRotation(0.0f, 0.0f, 0.0f);
}

Plane::~Plane()
{
	delete this->m_cb;
	delete this->m_ib;
	delete this->m_vb;
}

void Plane::update(float deltaTime)
{

}

void Plane::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	DeviceContext* deviceContext = m_system->getImmediateDeviceContext();

	constant cc = {};

	Matrix4x4 allMatrix;
	allMatrix.setIdentity();

	Matrix4x4 translationMatrix;
	translationMatrix.setIdentity();
	translationMatrix.setTranslation(this->getLocalPosition());

	Matrix4x4 scaleMatrix;
	scaleMatrix.setIdentity();
	scaleMatrix.setScale(this->getLocalScale());


	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 zMatrix;
	zMatrix.setIdentity();
	zMatrix.setQuaternionRotation(rotation.m_z, 0, 0, 1);

	Matrix4x4 xMatrix;
	xMatrix.setIdentity();
	xMatrix.setQuaternionRotation(rotation.m_x, 1, 0, 0);

	Matrix4x4 yMatrix;
	yMatrix.setIdentity();
	yMatrix.setQuaternionRotation(rotation.m_y, 0, 1, 0);

	Matrix4x4 rotMatrix;
	rotMatrix.setIdentity();
	rotMatrix *= zMatrix;
	rotMatrix *= yMatrix;
	rotMatrix *= xMatrix;
	allMatrix *= rotMatrix;


	allMatrix *= scaleMatrix;
	allMatrix *= translationMatrix;
	cc.m_world = allMatrix;

	Matrix4x4 cameraMatrix = CameraManager::getInstance()->getCameraViewMatrix();
	cc.m_view = cameraMatrix;


	float aspectRatio = (float)width / (float)height;
	cc.m_proj.setPerspectiveFovLH(aspectRatio, aspectRatio, 0.1f, 1000.0f);

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

void Plane::setAnimSpeed(float multiplier)
{
	Cube::setAnimSpeed(multiplier);
}