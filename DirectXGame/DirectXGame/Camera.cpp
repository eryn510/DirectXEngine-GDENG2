#include "Camera.h"
#include "AppWindow.h"

Camera::Camera(std::string name) : AGameObject(name)
{
	this->setPosition(0.0f, 0.0f, -4.0f);
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
	Vector3D localPos = this->getLocalPosition();
	float x = localPos.m_x;
	float y = localPos.m_y;
	float z = localPos.m_z;
	float moveSpeed = 10.0f;

	if (this->mouseDown)
	{
		if (InputSystem::get()->isKeyDown('W'))
		{
			z += deltaTime * moveSpeed;
			this->setPosition(x, y, z);
			this->updateViewMatrix();
		}
		if (InputSystem::get()->isKeyDown('E'))
		{
			y += deltaTime * moveSpeed;
			this->setPosition(x, y, z);
			this->updateViewMatrix();
		}
		if (InputSystem::get()->isKeyDown('S'))
		{
			z -= deltaTime * moveSpeed;
			this->setPosition(x, y, z);
			this->updateViewMatrix();
		}
		if (InputSystem::get()->isKeyDown('Q'))
		{
			y -= deltaTime * moveSpeed;
			this->setPosition(x, y, z);
			this->updateViewMatrix();
		}
		if (InputSystem::get()->isKeyDown('A'))
		{
			x -= deltaTime * moveSpeed;
			this->setPosition(x, y, z);
			this->updateViewMatrix();
		}
		if (InputSystem::get()->isKeyDown('D'))
		{
			x += deltaTime * moveSpeed;
			this->setPosition(x, y, z);
			this->updateViewMatrix();
		}

	}
}

void Camera::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->localMatrix;
}

void Camera::onKeyDown(int key)
{
	
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const Point& mouse_pos)
{
	if (this->mouseDown)
	{
		Vector3D localRot = this->getLocalRotation();
		m_rot_x = localRot.m_x;
		m_rot_y = localRot.m_y;
		float z = localRot.m_z;

		float width = (AppWindow::getInstance()->getClientWindowRect().right - AppWindow::getInstance()->getClientWindowRect().left);
		float height = (AppWindow::getInstance()->getClientWindowRect().bottom - AppWindow::getInstance()->getClientWindowRect().top);

		m_rot_x += (mouse_pos.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
		m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;

		InputSystem::get()->setCursorPosition(Point(width / 2.0f, height / 2.0f));

		this->setRotation(m_rot_x, m_rot_y, z);
		this->updateViewMatrix();

	}
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
	this->localMatrix.setIdentity();
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

	temp.setIdentity();
	temp.setTranslation(this->getLocalPosition());
	worldCam *= temp;


	worldCam.inverse();
	this->localMatrix = worldCam;
}

