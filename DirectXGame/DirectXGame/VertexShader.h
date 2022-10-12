#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class VertexShader
{
public:
	VertexShader(const void* shader_byte_code, size_t byte_code_size, RenderSystem* system);
	~VertexShader();

private:

private:
	ID3D11VertexShader* m_vs;
	RenderSystem* m_system = nullptr;

private:
	friend class GraphicsEngine;
	friend class DeviceContext;
	friend class RenderSystem;
};

