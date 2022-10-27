#pragma once
#include "Camera.h"

class CameraManager
{
public:
	static CameraManager* getInstance();
	static void initialize();
	static void destroy();

	void update();

	Matrix4x4 getCameraViewMatrix();

private:
	CameraManager();
	~CameraManager();
	CameraManager(CameraManager const&) {};
	CameraManager& operator=(CameraManager const&) {};
	static CameraManager* sharedInstance;

	Camera* sceneCamera;

};

