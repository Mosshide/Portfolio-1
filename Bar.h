#pragma once
#include "UIRectangle.h"
#include "UserInput.h"

class Bar : public Entity
{
public:
	Bar();
	~Bar();
	void update();
	void draw();
	void realign();
	void setBounds(int a, int b, int w);
	void reset();
	CollisionResult collision(LineSeg l, float *wratio = nullptr);

	float vel;

protected:
	UIRectangle _pic;
	int bound[2];
};