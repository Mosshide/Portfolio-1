#pragma once
#include "UIRectangle.h"
#include "Navigator.h"

class Ball : public Entity
{
public:
	Ball();
	~Ball();
	void update();
	void draw();
	void realign();
	void set();
	void launch(float horizontal);
	void bounceVert(float extraDistance);
	void bounceHor(float extraDistance);
	void damage(int d);
	LineSeg getTrajectory(int corner);

	bool isSet;
	bool gameOver;
	bool returnHome;
	int attack;

protected:
	Color _color;
	UIRectangle _pic;
	UIRectangle _healthBar[2];
	Navigator _nav;
	fRectangle _lastRect;
	int _maxHealth;
	int _health;
};