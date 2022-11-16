#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* system);
	void clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);

	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void setIndexBuffer(IndexBuffer* index_buffer);

	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);

	void setViewportSize(UINT width, UINT height);

	void setShaderConfig(VertexShader* vertex_shader, PixelShader* pixel_shader);

	void setTexture(Texture* texture);

	void setConstantBuffer(ConstantBuffer* buffer);

	~DeviceContext();

private:
	ID3D11DeviceContext* m_device_context;
	RenderSystem* m_system = nullptr;

private:
	friend class ConstantBuffer;
};

