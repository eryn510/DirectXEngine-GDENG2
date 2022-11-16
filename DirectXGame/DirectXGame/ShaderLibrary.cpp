#include "ShaderLibrary.h"
#include "GraphicsEngine.h"
#include <exception>
#include <iostream>

ShaderLibrary* ShaderLibrary::sharedInstance = NULL;

ShaderLibrary* ShaderLibrary::getInstance()
{
	return sharedInstance;
}

void ShaderLibrary::initialize()
{
	sharedInstance = new ShaderLibrary();
}

void ShaderLibrary::destroy()
{
	delete sharedInstance;
}

void ShaderLibrary::requestShaderData(String vertexShaderName, void** shaderByteCode, size_t* sizeShader)
{
	GraphicsEngine::getInstance()->getRenderSystem()->compileVertexShader(vertexShaderName.c_str(), "main", shaderByteCode, sizeShader);
}

VertexShader* ShaderLibrary::getVertexShader(String vertexShaderName)
{
	if (this->activeVertexShaders[vertexShaderName] == NULL)
		std::cout << "VertexShader not found!" << std::endl;

	return this->activeVertexShaders[vertexShaderName];
}

PixelShader* ShaderLibrary::getPixelShader(String pixelShaderName)
{
	if (this->activePixelShaders[pixelShaderName] == NULL)
		std::cout << "PixelShader not found!" << std::endl;

	return this->activePixelShaders[pixelShaderName];
}

ShaderLibrary::ShaderLibrary()
{
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	ShaderNames shaderNames;
	ShaderData shaderData;

	renderSystem->compileVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME.c_str(), "main", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[shaderNames.BASE_VERTEX_SHADER_NAME] = renderSystem->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);

	renderSystem->compilePixelShader(shaderNames.BASE_PIXEL_SHADER_NAME.c_str(), "main", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activePixelShaders[shaderNames.BASE_PIXEL_SHADER_NAME] = renderSystem->createPixelShader(shaderData.shaderByteCode, shaderData.sizeShader);

	renderSystem->compileVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME.c_str(), "main", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[shaderNames.TEXTURED_VERTEX_SHADER_NAME] = renderSystem->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);

	renderSystem->compilePixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME.c_str(), "main", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activePixelShaders[shaderNames.TEXTURED_PIXEL_SHADER_NAME] = renderSystem->createPixelShader(shaderData.shaderByteCode, shaderData.sizeShader);

	renderSystem->compileVertexShader(shaderNames.MESH_VERTEX_SHADER_NAME.c_str(), "main", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[shaderNames.MESH_VERTEX_SHADER_NAME] = renderSystem->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);

	std::cout << "Shader library initialized." << std::endl;
}

ShaderLibrary::~ShaderLibrary()
{
	
}
