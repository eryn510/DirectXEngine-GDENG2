#include "Camera.h"
#include "AppWindow.h"

Camera::Camera(std::string name) : AGameObject(name)
{
	this->setPosition(0.0f, 4.0f, -10.0f);
	//this->worldCameraMatrix.setTranslation(this->getLocalPosition());
	this->updateViewMatrix();
	InputSystem::get()->addListener(this);
}

Camera::~Camera()
{
	InputSystem::get()->removeListener(this);
}

void Camera::update(float deltaTime)
{
	
}

void Camera::draw(int width, int height)
{
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->viewCamera;
}

void Camera::onKeyDown(int key)
{
	
	if (InputSystem::get()->isKeyDown('W'))
	{
		m_forward = 1.0f;
	}
	if (InputSystem::get()->isKeyDown('S'))
	{
		m_forward = -1.0f;
	}
	if (InputSystem::get()->isKeyDown('A'))
	{
		m_right = -1.0f;
	}
	if (InputSystem::get()->isKeyDown('D'))
	{
		m_right = 1.0f;
	}
	if (this->mouseDown)
	{
		if (InputSystem::get()->isKeyDown('Q'))
		{
			m_up = -1.0f;
		}

		if (InputSystem::get()->isKeyDown('E'))
		{
			m_up = 1.0f;
		}
	}

	updateViewMatrix();
}

void Camera::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_right = 0.0f;
	m_up = 0.0f;
}

void Camera::onMouseMove(const Point& mouse_pos)
{
	Vector3D localRot = this->getLocalRotation();
	m_rot_x = localRot.m_x;
	m_rot_y = localRot.m_y;
	float z = localRot.m_z;

	float width = (AppWindow::getInstance()->getClientWindowRect().right - AppWindow::getInstance()->getClientWindowRect().left);
	float height = (AppWindow::getInstance()->getClientWindowRect().bottom - AppWindow::getInstance()->getClientWindowRect().top);

	m_rot_x -= (mouse_pos.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * MOUSE_SENSITIVITY;
	m_rot_y -= (mouse_pos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * MOUSE_SENSITIVITY;

	InputSystem::get()->setCursorPosition(Point(width / 2.0f, height / 2.0f));

	this->setRotation(m_rot_x, m_rot_y, z);
	this->updateViewMatrix();
}

void Camera::onLeftMouseDown(const Point& delta_mouse_pos)
{
}

void Camera::onLeftMouseUp(const Point& delta_mouse_pos)
{
}

void Camera::onRightMouseDown(const Point& delta_mouse_pos)
{
	this->mouseDown = true;
}

void Camera::onRightMouseUp(const Point& delta_mouse_pos)
{
	this->mouseDown = false;
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam;
	worldCam.setIdentity();
	Matrix4x4 temp;
	temp.setIdentity();

	Vector3D localRot = this->getLocalRotation();

	temp.setQuaternionRotation(localRot.m_x, 1, 0, 0);
	worldCam *= temp;

	temp.setIdentity();
	temp.setQuaternionRotation(localRot.m_y, 0, 1, 0);
	worldCam *= temp;


	//NEW POSITION FOR FREECAM MOVEMENT
	temp.setIdentity();
	Vector3D new_pos = localMatrix.getTranslation() + worldCam.getZDirection() * (m_forward * speed);
	new_pos = new_pos + worldCam.getXDirection() * (m_right * speed);
	new_pos = new_pos + worldCam.getYDirection() * (m_up * speed);
	temp.setTranslation(new_pos);
	worldCam *= temp;
	localMatrix = worldCam;



	worldCam.inverse();
	this->viewCamera = worldCam;
}

