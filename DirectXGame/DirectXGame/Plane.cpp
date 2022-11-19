#include "Plane.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "InputSystem.h"
#include "ShaderLibrary.h"
#include "PhysicsSystem.h"

Plane::Plane(std::string name, Texture* texture) : AGameObject(name)
{
	ShaderNames shaderNames;
	void* shader_byte_codes = NULL;
	size_t size_shaders = 0;
	ShaderLibrary::getInstance()->requestShaderData(shaderNames.BASE_VERTEX_SHADER_NAME, &shader_byte_codes, &size_shaders);

	vertex quad_list[]
	{
		//	X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f, -0.5f, -0.5f),	Vector3D(1,1,1),   Vector3D(1,1,1)}, //POS1
		{Vector3D(-0.5f, 0.5f, -0.5f),	Vector3D(1,1,1),   Vector3D(1,1,1)}, //POS2
		{Vector3D(0.5f, 0.5f, -0.5f),	Vector3D(1,1,1),   Vector3D(1,1,1)}, //POS3
		{Vector3D(0.5f, -0.5f, -0.5f),	Vector3D(1,1,1),   Vector3D(1,1,1)}, //POS4

		//BACK FACE
		{Vector3D(0.5f, -0.5f, 0.5f),	Vector3D(1,1,1),   Vector3D(1,1,1)}, //POS5
		{Vector3D(0.5f, 0.5f, 0.5f),		Vector3D(1,1,1),   Vector3D(1,1,1)}, //POS6
		{Vector3D(-0.5f, 0.5f, 0.5f),	Vector3D(1,1,1),   Vector3D(1,1,1)}, //POS7
		{Vector3D(-0.5f, -0.5f, 0.5f),	Vector3D(1,1,1),   Vector3D(1,1,1)} //POS8
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
	this->m_ib = m_system->createIndexBuffer(index_list, ARRAYSIZE(index_list));

	//VERTEX BUFFER Creation
	this->m_vb = m_system->createVertexBuffer(quad_list, sizeof(vertex), ARRAYSIZE(quad_list), shader_byte_codes, size_shaders);

	//CONSTANT BUFFER Creation
	constant cc;
	cc.m_time = 0;
	this->m_cb = m_system->createConstantBuffer(&cc, sizeof(constant));

	this->setPosition(0.0f, -5.0f, 0.0f);
	this->setScale(100.0f, 1.0f, 100.0f);
	this->setRotation(0.0f, 0.0f, 0.0f);
	this->updateLocalMatrix();
	this->attachComponent(new PhysicsComponent("PhysicsComponent", this));

	PhysicsComponent* component = (PhysicsComponent*)this->findComponentOfType(AComponent::ComponentType::Physics, "PhysicsComponent");
	component->getRigidBody()->setType(BodyType::KINEMATIC);

	std::cout << this->getComponentsOfTypeRecursive(AComponent::ComponentType::Physics).size() << std::endl;
}

Plane::~Plane()
{
	delete this->m_cb;
	delete this->m_ib;
	delete this->m_vb;
}

void Plane::awake()
{

}

void Plane::update(float deltaTime)
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

void Plane::draw(int width, int height)
{
	//set SHADERS
	ShaderNames shaderNames;
	m_system->getImmediateDeviceContext()->setShaderConfig
	(ShaderLibrary::getInstance()->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME),
		ShaderLibrary::getInstance()->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME));

	DeviceContext* deviceContext = m_system->getImmediateDeviceContext();

	constant cc = {};
	cc.m_world.setIdentity();

	if (this->overrideMatrix) {
		cc.m_world = this->localMatrix;
	}
	else {
		this->updateLocalMatrix();
		cc.m_world = this->localMatrix;
	}

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

void Plane::setAnimSpeed(float multiplier)
{
	
}