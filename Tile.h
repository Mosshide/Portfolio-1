#pragma once
#include "UIRectangle.h"

class Tile : public Entity
{
public:
	Tile();
	~Tile();
	void update();
	void draw();
	void realign();
	void reset();
	void damage(int d);
	CollisionResult collision(LineSeg l);

	bool alive;

protected:
	UIRectangle _pic;
	int _maxHealth;
	int _health;
};