#define _USE_MATH_DEFINES
#include "Circle.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include <cmath>

Circle::Circle(std::string name) : AGameObject(name)
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

		//std::cout << index_list[i] << "," << index_list[i + 1] << "," << index_list[i + 2] << std::endl;
	}

	index_list[(arcCount * 3) - 3] = 0;
	index_list[(arcCount * 3) - 2] = arcCount - 1;
	index_list[(arcCount * 3) - 1] = 1;


	for (int j = 0; j < arcCount; j++)
	{
		this->vertex_list[j].position = Vector3D(vertexPoints[j].m_x, vertexPoints[j].m_y, vertexPoints[j].m_z);
		this->vertex_list[j].color = Vector3D(1, 1, 1);
		this->vertex_list[j].color1 = Vector3D(0, 0, 1);
	}

	//INDEX BUFFER Creation
	UINT size_index_list = ARRAYSIZE(index_list);
	this->m_ib = m_system->createIndexBuffer(index_list, size_index_list);

	void* shader_byte_codes = nullptr;
	size_t size_shaders = 0;

	//VERTEX SHADER
	m_system->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_codes, &size_shaders);
	m_vs = m_system->createVertexShader(shader_byte_codes, size_shaders);


	//VERTEX BUFFER Creation
	UINT size_list = ARRAYSIZE(this->vertex_list);
	this->m_vb = m_system->createVertexBuffer(this->vertex_list, sizeof(vertex), size_list, shader_byte_codes, size_shaders);


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

Circle::~Circle()
{
	delete this->m_cb;
	delete this->m_ib;
	delete this->m_vb;
}

void Circle::update(float deltaTime)
{
	if (this->canUpdate)
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
}

void Circle::draw(int width, int height)
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

void Circle::setAnimSpeed(float multiplier)
{
	this->animSpeed = multiplier;
}