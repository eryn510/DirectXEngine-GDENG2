#pragma once
#include "AppWindow.h"

class DeviceContext;

class ConstantBuffer
{
public:
	ConstantBuffer();
	bool load(void* buffer, UINT size_buffer);
	void update(DeviceContext* context, void* buffer);
	bool release();
	~ConstantBuffer();

private:
	ID3D11Buffer* m_buffer;

private:
	friend class DeviceContext;
};

