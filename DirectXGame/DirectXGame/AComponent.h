#pragma once
#include <string>

class AGameObject;
class AComponent
{
public:
	typedef std::string String;
	enum ComponentType {NotSet = -1, Script = 0, Renderer = 1, Input = 2, Physics = 3};
	AComponent(String name, ComponentType type, AGameObject* owner) : name(name), type(type), owner(owner)
	{
		
	};
	~AComponent() 
	{

	};

	void attachOwner(AGameObject* owner) 
	{
		this->owner = owner;
	};
	void detachOwner() 
	{
		this->owner = nullptr;
		delete this;
	};
	AGameObject* getOwner() 
	{
		return this->owner;
	};
	ComponentType getType() 
	{
		return this->type;
	};
	String getName() 
	{
		return this->name;
	};

	virtual void perform(float deltaTime) = 0;

protected:
	AGameObject* owner;
	ComponentType type;
	String name;
};