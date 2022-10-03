#include "Cube.h"

Cube::Cube(vertex vertex_list[])
{
	memcpy(m_vertex_list, vertex_list, sizeof(vertex_list));
	createCube();
}

Cube::~Cube()
{

}

void Cube::createCube()
{
	///*
	//RECTANGLE RAINBOW
	//*/

	/*
	//TRIANGLE RAINBOW
	vertex list[]
	{
		//	X - Y - Z	TRI
		{-0.5, -0.5, 0.0f,		1,0,0}, //POS1
		{0, 0.5, 0.0f,		0,1,0}, //POS2
		{0.5, -0.5, 0.0f,		0,0,1}, //POS3
	};
	*/

	/*
	//RECTANGLE GREEN
	vertex list[]
	{
		//	X - Y - Z	QUAD
		{-0.5, -0.5, 0.0f,		0,1,0}, //POS1
		{-0.5, 0.5, 0.0f,		0,1,0}, //POS2
		{0.5, -0.5, 0.0f,		0,1,0}, //POS3
		{0.5, 0.5, 0.0f,		0,1,0} //POS4
	};
	*/

	vertex vertex_list[]
	{
		//	X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f, -0.5f, -0.5f), Vector3D(1, 0, 0), Vector3D(0.2f, 0, 0)}, //POS1
		{ Vector3D(-0.5f, 0.5f, -0.5f),		Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0) }, //POS2
		{ Vector3D(0.5f, 0.5f, -0.5f),		Vector3D(1,1,0),    Vector3D(0.2f,0.2f,0) }, //POS3
		{ Vector3D(0.5f, -0.5f, -0.5f),		Vector3D(1,0,0),    Vector3D(0.2f,0,0) }, //POS4

		//BACK FACE
		{ Vector3D(0.5f, -0.5f, 0.5f),		Vector3D(0,1,0),    Vector3D(0,0.2f,0) }, //POS5
		{ Vector3D(0.5f, 0.5f, 0.5f),		Vector3D(0,1,1),    Vector3D(0,0.2f,0.2f) }, //POS6
		{ Vector3D(-0.5f, 0.5f, 0.5f),		Vector3D(0,1,1),    Vector3D(0,0.2f,0.2f) }, //POS7
		{ Vector3D(-0.5f, -0.5f, 0.5f),		Vector3D(0,1,0),    Vector3D(0,0.2f,0) } //POS8
	};

	appInstance->m_vb = graphEngine->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2, //FIRST TRIANGLE
		2,3,0, //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	appInstance->m_ib = graphEngine->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	appInstance->m_ib->load(index_list, size_index_list);


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	//Vertex Shader
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	appInstance->m_vs = graphEngine->createVertexShader(shader_byte_code, size_shader);

	appInstance->m_vb->load(m_vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader();

	//Pixel Shader
	graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	appInstance->m_ps = graphEngine->createPixelShader(shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader();
}
