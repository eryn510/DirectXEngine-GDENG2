#include "Cube.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "InputSystem.h"
#include "CameraManager.h"

Cube::Cube(std::string name) : AGameObject(name)
{
	vertex quad_list[]
	{
		//	X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f, -0.5f, -0.5f),	Vector3D(-0.5f, -0.5f, -0.5f),	Vector3D(1,0,0),   Vector3D(1,0,0)}, //POS1
		{Vector3D(-0.5f, 0.5f, -0.5f),	Vector3D(-0.5f, 0.5f, -0.5f),	Vector3D(1,1,0),   Vector3D(1,1,0)}, //POS2
		{Vector3D(0.5f, 0.5f, -0.5f),	Vector3D(0.5f, 0.5f, -0.5f),	Vector3D(1,1,0),   Vector3D(1,1,0)}, //POS3
		{Vector3D(0.5f, -0.5f, -0.5f),	Vector3D(0.5f, -0.5f, -0.5f),	Vector3D(1,0,0),   Vector3D(1,0,0)}, //POS4

		//BACK FACE
		{Vector3D(0.5f, -0.5f, 0.5f),	Vector3D(0.5f, -0.5f, 0.5f),	Vector3D(0,1,0),   Vector3D(0,1,0)}, //POS5
		{Vector3D(0.5f, 0.5f, 0.5f),	Vector3D(0.5f, 0.5f, 0.5f),		Vector3D(0,1,1),   Vector3D(0,1,1)}, //POS6
		{Vector3D(-0.5f, 0.5f, 0.5f),	Vector3D(-0.5f, 0.5f, 0.5f),	Vector3D(0,1,1),   Vector3D(0,1,1)}, //POS7
		{Vector3D(-0.5f, -0.5f, 0.5f),	Vector3D(-0.5f, -0.5f, 0.5f),	Vector3D(0,1,0),   Vector3D(0,1,0)} //POS8
	};


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

	//INDEX BUFFER Creation
	UINT size_index_list = ARRAYSIZE(index_list);
	this->m_ib = m_system->createIndexBuffer(index_list, size_index_list);
	
	void* shader_byte_codes = nullptr;
	size_t size_shaders = 0;

	//VERTEX SHADER
	m_system->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_codes, &size_shaders);
	m_vs = m_system->createVertexShader(shader_byte_codes, size_shaders);


	//VERTEX BUFFER Creation
	UINT size_list = ARRAYSIZE(quad_list);
	this->m_vb = m_system->createVertexBuffer(quad_list, sizeof(vertex), size_list, shader_byte_codes, size_shaders);
	

	m_system->releaseCompiledShader();

	//PIXEL SHADER
	m_system->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_codes, &size_shaders);
	m_ps = m_system->createPixelShader(shader_byte_codes, size_shaders);
	m_system->releaseCompiledShader();

	//CONSTANT BUFFER Creation
	constant cc;
	cc.m_time = 0;
	this->m_cb = m_system->createConstantBuffer(&cc, sizeof(constant));

	//set SHADERS
	m_system->getImmediateDeviceContext()->setVertexShader(this->m_vs);
	m_system->getImmediateDeviceContext()->setPixelShader(this->m_ps);
} 

Cube::~Cube()
{
	delete this->m_cb;
	delete this->m_ib;
	delete this->m_vb;
}

void Cube::update(float deltaTime)
{
	this->deltaTime = deltaTime;
	if (InputSystem::get()->isKeyDown('W'))
	{
		this->ticks += deltaTime;

		float rotSpeed = this->ticks * this->speed * this->animSpeed;
		this->setRotation(rotSpeed, rotSpeed, rotSpeed);
	}
	else if (InputSystem::get()->isKeyDown('S'))
	{
		this->ticks -= deltaTime;

		float rotSpeed = this->ticks * this->speed * this->animSpeed;
		this->setRotation(rotSpeed, rotSpeed, rotSpeed);
	}
}

void Cube::draw(int width, int height)
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

	deviceContext->setConstantBuffer(this->m_vs, this->m_cb);
	deviceContext->setConstantBuffer(this->m_ps, this->m_cb);

	deviceContext->setVertexBuffer(this->m_vb);
	deviceContext->setIndexBuffer(this->m_ib);

	deviceContext->drawIndexedTriangleList(this->m_ib->getSizeIndexList(), 0, 0);
}

void Cube::setAnimSpeed(float multiplier)
{
	this->animSpeed = multiplier;
}
