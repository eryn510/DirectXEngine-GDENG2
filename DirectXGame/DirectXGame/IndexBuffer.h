#pragma once
#include "AppWindow.h"
#include "Prerequisites.h"

class IndexBuffer
{
public:
	IndexBuffer(RenderSystem* system);
	bool load(void* list_indices, UINT size_list);
	UINT getSizeIndexList();
	bool release();
	~IndexBuffer();

private:
	UINT m_size_list;

private:
	ID3D11Buffer* m_buffer;
	RenderSystem* m_system = nullptr;

private:
	friend class DeviceContext;
};

