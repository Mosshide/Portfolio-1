#pragma once
#include "render.h"
#include "ToyBox.h"

class Camera : public Entity
{
public:
	Camera();
	~Camera();
	void update();
	void draw();
	void set(float x, float y, float z = 5.0);
	void offset();
	void setOverTime();
	void offsetOverTime();
	void shake();
	void realign();
};

extern Camera *gameCamera;