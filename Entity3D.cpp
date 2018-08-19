#include "Entity3D.h"

Entity3D::Entity3D()
{
}

Entity3D::~Entity3D()
{
}

void Entity3D::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
	position.x = x;
	position.y = y;
	position.z = z;

	realign();
}

void Entity3D::offsetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	position.x += x;
	position.y += y;
	position.z += z;

	realign();
}