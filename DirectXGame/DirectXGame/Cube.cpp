#include "Cube.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "InputSystem.h"
#include "CameraManager.h"
#include "ShaderLibrary.h"
#include "Mesh.h"
#include <cmath>

Cube::Cube(std::string name, Texture* texture, Mesh* mesh) : AGameObject(name)
{
	Vector3D position_list[]
	{
		Vector3D(-0.5f, -0.5f, -0.5f),//POS1
		Vector3D(-0.5f, 0.5f, -0.5f),//POS2
		Vector3D(0.5f, 0.5f, -0.5f),//POS3
		Vector3D(0.5f, -0.5f, -0.5f), //POS4

		//BACK FACE
		Vector3D(0.5f, -0.5f, 0.5f),//POS5
		Vector3D(0.5f, 0.5f, 0.5f), //POS6
		Vector3D(-0.5f, 0.5f, 0.5f), //POS7
		Vector3D(-0.5f, -0.5f, 0.5f) //POS8
	};

	memcpy(this->position_list, position_list, sizeof(Vector3D) * 8);

	ShaderNames shaderNames;
	void* shader_byte_codes = NULL;
	size_t size_shaders = 0;

	if (texture == NULL)
	{
		ShaderLibrary::getInstance()->requestShaderData(shaderNames.BASE_VERTEX_SHADER_NAME, &shader_byte_codes, &size_shaders);
		setAlbedoVertex();

		//VERTEX BUFFER Creation
		this->m_vb = m_system->createVertexBuffer(this->vertex_list, sizeof(vertex), ARRAYSIZE(this->vertex_list), shader_byte_codes, size_shaders);
	}
		
	else 
	{
		ShaderLibrary::getInstance()->requestShaderData(shaderNames.TEXTURED_VERTEX_SHADER_NAME, &shader_byte_codes, &size_shaders);
		setTextureVertex();

		this->m_vb = m_system->createVertexBuffer(this->texturevertex_list, sizeof(texturevertex), ARRAYSIZE(this->texturevertex_list), shader_byte_codes, size_shaders, true);
	}
		
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
	
	//CONSTANT BUFFER Creation
	constant cc;
	cc.m_time = 0;
	this->m_cb = m_system->createConstantBuffer(&cc, sizeof(constant));

	this->setTexture(texture);
	this->setMesh(mesh);
} 

Cube::~Cube()
{
	delete this->m_cb;
	delete this->m_ib;
	delete this->m_vb;
}

void Cube::update(float deltaTime)
{
	if(this->canUpdate)
	{
		this->deltaTime = deltaTime;

		if (InputSystem::get()->isKeyDown('W') || true)
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

void Cube::draw(int width, int height)
{
	//set SHADERS
	ShaderNames shaderNames;

	if (this->texture == NULL) {
		m_system->getImmediateDeviceContext()->setShaderConfig
		(ShaderLibrary::getInstance()->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME),
			ShaderLibrary::getInstance()->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME));
	}
	else 
	{
		m_system->getImmediateDeviceContext()->setTexture(this->texture);
		m_system->getImmediateDeviceContext()->setShaderConfig(ShaderLibrary::getInstance()->getVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME),
			ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME));
	}
	
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

	if (mesh == NULL) 
	{
		deviceContext->setVertexBuffer(this->m_vb);
		deviceContext->setIndexBuffer(this->m_ib);
		deviceContext->drawIndexedTriangleList(this->m_ib->getSizeIndexList(), 0, 0);
	}
	else 
	{
		deviceContext->setVertexBuffer(this->mesh->getVertexBuffer());
		deviceContext->setIndexBuffer(this->mesh->getIndexBuffer());
		deviceContext->drawIndexedTriangleList(this->mesh->getIndexBuffer()->getSizeIndexList(), 0, 0);
	}

}

void Cube::setAnimSpeed(float multiplier)
{
	this->animSpeed = multiplier;
}

void Cube::setAlbedoVertex()
{
	vertex quad_list[]
	{
		//	X - Y - Z
		//FRONT FACE
		{this->position_list[0],	Vector3D(1,0,0),   Vector3D(1,0,0)}, //POS1
		{this->position_list[1],	Vector3D(1,1,0),   Vector3D(1,1,0)}, //POS2
		{this->position_list[2],	Vector3D(1,1,1),   Vector3D(1,1,1)}, //POS3
		{this->position_list[3],	Vector3D(1,0,1),   Vector3D(1,0,1)}, //POS4

		//BACK FACE
		{this->position_list[4],	Vector3D(0,1,0),   Vector3D(0,1,0)}, //POS5
		{this->position_list[5],	Vector3D(0,1,1),   Vector3D(0,1,1)}, //POS6
		{this->position_list[6],	Vector3D(1,1,1),   Vector3D(1,1,1)}, //POS7
		{this->position_list[7],	Vector3D(1,1,0),   Vector3D(1,1,0)} //POS8
	};

	memcpy(this->vertex_list, quad_list, sizeof(vertex) * 8);
}

void Cube::setTextureVertex()
{
	Vector2D texcoord_list[] =
	{
		{ Vector2D(0.0f,0.0f) },
		{ Vector2D(0.0f,1.0f) },
		{ Vector2D(1.0f,0.0f) },
		{ Vector2D(1.0f,1.0f) }
	};

	texturevertex quadList[] =
	{
		//X - Y - Z
		//FRONT FACE
		{ this->position_list[0],texcoord_list[1] },
		{ this->position_list[1],texcoord_list[0] },
		{ this->position_list[2],texcoord_list[2] },
		{ this->position_list[3],texcoord_list[3] },


		{ this->position_list[4],texcoord_list[1] },
		{ this->position_list[5],texcoord_list[0] },
		{ this->position_list[6],texcoord_list[2] },
		{ this->position_list[7],texcoord_list[3] },


		{ this->position_list[1],texcoord_list[1] },
		{ this->position_list[6],texcoord_list[0] },
		{ this->position_list[5],texcoord_list[2] },
		{ this->position_list[2],texcoord_list[3] },

		{ this->position_list[7],texcoord_list[1] },
		{ this->position_list[0],texcoord_list[0] },
		{ this->position_list[3],texcoord_list[2] },
		{ this->position_list[4],texcoord_list[3] },

		{ this->position_list[3],texcoord_list[1] },
		{ this->position_list[2],texcoord_list[0] },
		{ this->position_list[5],texcoord_list[2] },
		{ this->position_list[4],texcoord_list[3] },

		{ this->position_list[7],texcoord_list[1] },
		{ this->position_list[6],texcoord_list[0] },
		{ this->position_list[1],texcoord_list[2] },
		{ this->position_list[0],texcoord_list[3] }
	};

	memcpy(this->texturevertex_list, quadList, sizeof(texturevertex) * 24);
}
