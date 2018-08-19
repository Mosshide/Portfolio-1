#include "Camera.h"

Camera::Camera()
{
	//setPosition(0, 0);
	//setSize(render->getScreenWidth(), render->getScreenHeight());
	//set(0.f, 1.f, 0.f);
}

Camera::~Camera()
{
}

void Camera::update()
{

}

void Camera::draw()
{

}

void Camera::set(float x, float y, float z)
{
	toyBox->shader->setCamera(glm::vec3(x, y, z), glm::vec3(0, M_PI / 2.0, 0), glm::vec3(0, 0, 1));
}

void Camera::offset()
{

}

void Camera::setOverTime()
{

}

void Camera::offsetOverTime()
{

}

void Camera::shake()
{

}

void Camera::realign()
{

}

Camera *gameCamera;