#include "Quad.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "ShaderLibrary.h"

Quad::Quad(std::string name) : AGameObject(name)
{
	ShaderNames shaderNames;
	void* shader_byte_codes = NULL;
	size_t size_shaders = 0;
	ShaderLibrary::getInstance()->requestShaderData(shaderNames.BASE_VERTEX_SHADER_NAME, &shader_byte_codes, &size_shaders);

	vertex quad_list[]
	{
		//	X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f, -0.5f, 0.0f),	Vector3D(1,0,0),    Vector3D(0.2f,0,0)}, //POS1
		{Vector3D(-0.5f, 0.5f, 0.0f),	Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0)}, //POS2
		{Vector3D(0.5f, 0.5f, 0.0f),		Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0)}, //POS3
		{Vector3D(0.5f, -0.5f, 0.0f),	Vector3D(1,0,0),    Vector3D(0.2f,0,0)}, //POS4
	};

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2, //FIRST TRIANGLE
		2,3,0, //SECOND TRIANGLE
	};

	//INDEX BUFFER Creation
	this->m_ib = m_system->createIndexBuffer(index_list, ARRAYSIZE(index_list));

	//VERTEX BUFFER Creation
	this->m_vb = m_system->createVertexBuffer(quad_list, sizeof(vertex), ARRAYSIZE(quad_list), shader_byte_codes, size_shaders);

	//CONSTANT BUFFER Creation
	constant cc;
	cc.m_time = 0;
	this->m_cb = m_system->createConstantBuffer(&cc, sizeof(constant));
}

Quad::~Quad()
{
	delete this->m_cb;
	delete this->m_ib;
	delete this->m_vb;
}

void Quad::awake()
{

}

void Quad::update(float delta)
{
	if(this->canUpdate)
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

void Quad::draw(int width, int height)
{
	//set SHADERS
	ShaderNames shaderNames;
	m_system->getImmediateDeviceContext()->setShaderConfig
	(ShaderLibrary::getInstance()->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME),
		ShaderLibrary::getInstance()->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME));

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


	allMatrix *= scaleMatrix;

	Matrix4x4 rotMatrix;
	rotMatrix.setIdentity();
	rotMatrix *= zMatrix;
	rotMatrix *= yMatrix;
	rotMatrix *= xMatrix;
	allMatrix *= rotMatrix;

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

	deviceContext->setConstantBuffer(this->m_cb);
	deviceContext->setVertexBuffer(this->m_vb);
	deviceContext->setIndexBuffer(this->m_ib);

	deviceContext->drawIndexedTriangleList(this->m_ib->getSizeIndexList(), 0, 0);
}

void Quad::setAnimSpeed(float multiplier)
{
	this->animSpeed = multiplier;
}