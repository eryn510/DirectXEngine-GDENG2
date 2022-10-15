#pragma once
#include "Camera.h"

class CameraManager
{
public:
	static CameraManager* getInstance();
	static void initialize();
	static void destroy();

	void update(); //TODO: Game object manager should perform update of all game objects

	Matrix4x4 getCameraViewMatrix();

private:
	CameraManager();
	~CameraManager();
	CameraManager(CameraManager const&) {};             // copy constructor is private
	CameraManager& operator=(CameraManager const&) {};  // assignment operator is private*/
	static CameraManager* sharedInstance;

	Camera* sceneCamera;

};

