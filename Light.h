#pragma once
#include "Entity3D.h"
#include "Model.h"

class Light : public Entity3D
{
public:
	Light();
	~Light();
	void update();
	void draw();
	void realign();
	void setMagnitude(GLfloat m);

	Shader *shader;
	int light;

private:
	GLfloat _magnitude;
	GLfloat _coverage;
	Color _color;

	Model _model;
};