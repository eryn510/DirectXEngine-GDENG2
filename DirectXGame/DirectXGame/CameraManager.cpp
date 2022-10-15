#include "CameraManager.h"

CameraManager* CameraManager::sharedInstance = NULL;

CameraManager* CameraManager::getInstance()
{
	return sharedInstance;
}

void CameraManager::initialize()
{
	sharedInstance = new CameraManager();
}

void CameraManager::destroy()
{
	delete sharedInstance;
}

void CameraManager::update()
{
	this->sceneCamera->update(EngineTime::getDeltaTime());
}

Matrix4x4 CameraManager::getCameraViewMatrix()
{
	return this->sceneCamera->getViewMatrix();
}

CameraManager::CameraManager()
{
	this->sceneCamera = new Camera("SceneCamera");
}

CameraManager::~CameraManager()
{
	delete this->sceneCamera;
}
