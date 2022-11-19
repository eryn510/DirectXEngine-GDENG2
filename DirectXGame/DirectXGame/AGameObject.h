#pragma once
#include "EngineTime.h"
#include "Prerequisites.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "Texture.h"
#include "AComponent.h"

class AGameObject
{
public:
	typedef std::string String;
	typedef std::vector<AComponent*> ComponentList;

	AGameObject(std::string name);

	~AGameObject();

public:
	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height) = 0; 
	virtual void setAnimSpeed(float deltaTime) = 0;
	bool canUpdate = false;

	void setTexture(Texture* texture);
	void setMesh(Mesh* mesh);

	//POSITION
	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	//SCALE
	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	//ROTATION
	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rotate);
	Vector3D getLocalRotation();

	std::string getName();

	//COMPONENT
	void attachComponent(AComponent* component);
	void detachComponent(AComponent* component);

	AComponent* findComponentByName(String name);
	AComponent* findComponentOfType(AComponent::ComponentType type, String name);
	ComponentList getComponentsOfType(AComponent::ComponentType type);
	ComponentList getComponentsOfTypeRecursive(AComponent::ComponentType type);


	void updateLocalMatrix(); //updates local matrix based from latest position, rotation, and scale.
	void recomputeMatrix(float matrix[16]);
	float* getRawMatrix();
	float* getPhysicsLocalMatrix();

	struct vertex
	{
		Vector3D position;
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

	ComponentList componentList;

	bool overrideMatrix = false;

	virtual void awake() = 0;

	Texture* texture = NULL;
	Mesh* mesh = NULL;
};