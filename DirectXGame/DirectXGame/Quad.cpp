#include "Quad.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

Quad::Quad(std::string name, void* shader_byte_code, size_t size_shader) : AGameObject(name)
{
	vertex quad_list[]
	{
		//	X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f, -0.5f, 0.0f),  Vector3D(-0.5f, -0.5f, 0.0f),		Vector3D(1,0,0),    Vector3D(0.2f,0,0)}, //POS1
		{Vector3D(-0.5f, 0.5f, 0.0f),	Vector3D(-0.5f, 0.5f, 0.0f),	Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0)}, //POS2
		{Vector3D(0.5f, 0.5f, 0.0f),	Vector3D(0.5f, 0.5f, 0.0f),	Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0)}, //POS3
		{Vector3D(0.5f, -0.5f, 0.0f),	Vector3D(0.5f, -0.5f, 0.0f),	Vector3D(1,0,0),    Vector3D(0.2f,0,0)}, //POS4
	};

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2, //FIRST TRIANGLE
		2,3,0, //SECOND TRIANGLE
	};

	//Vertex Buffer Creation
	UINT size_list = ARRAYSIZE(quad_list);
	this->m_vb = m_system->createVertexBuffer(quad_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	//Index Buffer Creation
	UINT size_index_list = ARRAYSIZE(index_list);
	this->m_ib = m_system->createIndexBuffer(index_list, size_index_list);

	//Constant Buffer Creation
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

void Quad::update(float delta)
{

}

void Quad::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	DeviceContext* deviceContext = m_system->getImmediateDeviceContext();

	constant cc = {};

	/*
	if (this->deltaPos > 1.0f)
		this->deltaPos = 0.0f;
	else
		this->deltaPos += this->deltaTime * 0.1f;
	*/

	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->getLocalScale());
	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.m_z);
	Matrix4x4 xMatrix; zMatrix.setRotationX(rotation.m_x);
	Matrix4x4 yMatrix; zMatrix.setRotationY(rotation.m_y);

	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix * xMatrix * yMatrix * zMatrix;
	allMatrix = allMatrix * scaleMatrix * rotMatrix;
	allMatrix *= translationMatrix;
	cc.m_world = allMatrix;

	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);

	this->m_cb->update(deviceContext, &cc);

	deviceContext->setConstantBuffer(vertexShader, this->m_cb);
	deviceContext->setConstantBuffer(pixelShader, this->m_cb);

	deviceContext->setIndexBuffer(this->m_ib);
	deviceContext->setVertexBuffer(this->m_vb);
	deviceContext->drawIndexedTriangleList(this->m_ib->getSizeIndexList(), 0, 0);
}

void Quad::setAnimSpeed(float deltaTime)
{
}