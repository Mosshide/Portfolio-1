#pragma once
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include "Color.h"
#include <cstdio>
#include <cmath>
#include <string>
#include "Physics.h"

class Entity3D
{
public:
	Entity3D();
	~Entity3D();
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void realign() {};

	virtual void setPosition(GLfloat x, GLfloat y, GLfloat z);
	virtual void setPosition(glm::vec3 v) { setPosition(v.x, v.y, v.z); }
	//virtual void setPosition(int x, int y) { setPosition((GLfloat)x, (GLfloat)y); }

	virtual void offsetPosition(GLfloat x, GLfloat y, GLfloat z);
	virtual void offsetPosition(glm::vec3 v) { offsetPosition(v.x, v.y, v.z); }
	//virtual void offsetPosition(int x, int y) { offsetPosition((GLfloat)x, (GLfloat)y); }

	glm::vec3 position;
	glm::vec3 scalar;
	glm::vec3 rotation;
};
