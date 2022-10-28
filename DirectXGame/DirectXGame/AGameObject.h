#pragma once
#include "EngineTime.h"
#include "Prerequisites.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"

class AGameObject
{
public:
	AGameObject(std::string name)
	{
		this->name = name;
		this->localRotation = Vector3D::zeros();
		this->localPosition = Vector3D::zeros();
		this->localScale = Vector3D::ones();
	}

	~AGameObject()
	{
		
	}

public:
	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height) = 0;
	bool canUpdate = false;

	void setPosition(float x, float y, float z)
	{
		this->localPosition = Vector3D(x, y, z);
	};
	void setPosition(Vector3D pos)
	{
		this->localPosition = pos;
	};
	Vector3D getLocalPosition()
	{
		return this->localPosition;
	};

	void setScale(float x, float y, float z)
	{
		this->localScale = Vector3D(x, y, z);
	};
	void setScale(Vector3D scale)
	{
		this->localScale = scale;
	};
	Vector3D getLocalScale()
	{
		return this->localScale;
	};

	void setRotation(float x, float y, float z)
	{
		this->localRotation = Vector3D(x, y, z);
	};
	void setRotation(Vector3D rotate)
	{
		this->localRotation = rotate;
	};
	Vector3D getLocalRotation()
	{
		return this->localRotation;
	};

	std::string getName()
	{
		return this->name;
	};

	struct vertex
	{
		Vector3D position;
		Vector3D position1;
		Vector3D color;
		Vector3D color1;
	};

	_declspec(align(16))
	struct constant
	{
		Matrix4x4 m_world;
		Matrix4x4 m_view;
		Matrix4x4 m_proj;
		unsigned int m_time;
	};

protected:
	std::string name;
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;
};