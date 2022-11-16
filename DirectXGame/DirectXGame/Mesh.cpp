#include "Mesh.h"
#include "GraphicsEngine.h"
#include "VertexMesh.h"
#include "ShaderLibrary.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <locale>
#include <codecvt>

Mesh::Mesh(const wchar_t* full_path) : Resource(full_path)
{
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	std::wstring ws(full_path);
	std::string inputfile(ws.begin(), ws.end());

	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputfile.c_str());

	if (!err.empty())
		throw std::exception("Mesh not created successfully");

	if (!res)
		throw std::exception("Mesh not created successfully");

	if (shapes.size() > 1)
		throw std::exception("Mesh not created successfully");

	
	std::vector<VertexMesh> list_vertices;
	std::vector<unsigned int> list_indices;

	size_t vertex_buffer_size = 0;


	for (size_t s = 0; s < shapes.size(); s++)
	{
		vertex_buffer_size += shapes[s].mesh.indices.size();
	}

	list_vertices.reserve(vertex_buffer_size);
	list_indices.reserve(vertex_buffer_size);

	size_t index_global_offset = 0;

	for (size_t s = 0; s < shapes.size(); s++)
	{
		size_t index_offset = 0;

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

			Vector3D vertices_face[3];
			Vector2D texcoords_face[3];

			for (unsigned char v = 0; v < num_face_verts; v++)
			{
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = attribs.vertices[(int)index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attribs.vertices[(int)index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[(int)index.vertex_index * 3 + 2];

				tinyobj::real_t tx = 0;
				tinyobj::real_t ty = 0;
				if (attribs.texcoords.size())
				{
					tx = attribs.texcoords[(int)index.texcoord_index * 2 + 0];
					ty = attribs.texcoords[(int)index.texcoord_index * 2 + 1];
				}
				vertices_face[v] = Vector3D(vx, vy, vz);
				texcoords_face[v] = Vector2D(tx, ty);

				VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty));
				list_vertices.push_back(vertex);

				list_indices.push_back((unsigned int)index_global_offset + v);
			}


			index_offset += num_face_verts;
			index_global_offset += num_face_verts;
		}
	}

	RenderSystem* m_system = GraphicsEngine::getInstance()->getRenderSystem();

	void* shader_byte_code = NULL;
	size_t size_shader = 0;

	ShaderNames shaderNames;
	ShaderLibrary::getInstance()->requestShaderData(shaderNames.MESH_VERTEX_SHADER_NAME, &shader_byte_code, &size_shader);

	this->m_ib = m_system->createIndexBuffer(&list_indices[0], (UINT)list_indices.size());
	this->m_vb = m_system->createVertexBuffer(&list_vertices[0], sizeof(VertexMesh), (UINT)list_vertices.size(), shader_byte_code, (UINT)size_shader, true);
}

Mesh::~Mesh()
{

}

VertexBuffer* Mesh::getVertexBuffer() 
{
	return m_vb;
}

IndexBuffer* Mesh::getIndexBuffer()
{
	return m_ib;
}


void Mesh::setTexture(Texture* texture)
{
	this->m_texture = texture;
}

void Mesh::draw() 
{
	DeviceContext* deviceContext = GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext();

	ShaderNames shaderNames;
	deviceContext->setTexture(this->m_texture);
	deviceContext->setShaderConfig(ShaderLibrary::getInstance()->getVertexShader(shaderNames.MESH_VERTEX_SHADER_NAME),
		ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME));

	deviceContext->setVertexBuffer(this->m_vb);
	deviceContext->setIndexBuffer(this->m_ib);

	deviceContext->drawIndexedTriangleList(this->m_ib->getSizeIndexList(), 0, 0);
}