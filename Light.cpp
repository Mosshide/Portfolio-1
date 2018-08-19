#include "Light.h"

Light::Light()
{
	shader = toyBox->shader;
	_magnitude = 300.f;
	_coverage = 1.f;
	light = 0;

	_model.setColor(Color(yellow));
	_model.setModel("cube");
	_model.setTranslation(0, 0, 0);
	_model.setScalar(.1f);
}

Light::~Light()
{
	shader->setLight(glm::vec3(0.f, 0.f, 0.f), 0, light);
}

void Light::update()
{
	
}

void Light::draw()
{
	_model.draw();
}

void Light::realign()
{
	shader->setLight(position, _magnitude, light);
	_model.setTranslation(position);
}

void Light::setMagnitude(GLfloat m)
{
	_magnitude = m;
	shader->setLight(position, _magnitude, light);
}