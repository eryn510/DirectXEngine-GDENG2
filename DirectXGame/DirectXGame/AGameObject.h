#pragma once
#include "EngineTime.h"

class AGameObject
{
public:
	AGameObject(void* shader_byte_code, size_t size_shader)
	{
		
	}

	~AGameObject()
	{
		
	}

public:
	virtual void create() = 0;
	virtual void update() = 0;
	virtual void release() = 0;

};