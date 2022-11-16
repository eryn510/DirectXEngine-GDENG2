#pragma once
#include "AppWindow.h"
#include "Prerequisites.h"

class ConstantBuffer
{
public:
	ConstantBuffer(void* buffer, UINT size_buffer, RenderSystem* system);
	void update(DeviceContext* context, void* buffer);
	~ConstantBuffer();

	ID3D11Buffer* getCB();

private:
	ID3D11Buffer* m_buffer;
	RenderSystem* m_system = nullptr;

private:
	friend class DeviceContext;
};

