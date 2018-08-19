#include "Ball.h"

Ball::Ball()
{
	_pic.setTexture("blank");
	_color = Color(.4f, .4f, .4f, 1.f);
	_pic.setRGBA(_color);

	_healthBar[0].setTexture("blank");
	_healthBar[1].setTexture("blank");
	_healthBar[0].setRGBA(red);
	_healthBar[1].setRGBA(green);

	presence = fRectangle(0, 0, 32, 32);
	_nav.vel = { 0.f, 0.f };

	isSet = true;
	gameOver = false;
	returnHome = false;

	_maxHealth = 500;
	_health = _maxHealth;
	attack = 1;

	realign();
}

Ball::~Ball()
{
}

void Ball::update()
{
	_pic.setRGBA(_color);
	float _colorChange = .001f;
	if (_color.r > .4f) _color.r -= _colorChange;
	if (_color.r < .4f) _color.r = .4f;
	if (_color.g > .4f) _color.g -= _colorChange;
	if (_color.g < .4f) _color.g = .4f;
	if (_color.b > .4f) _color.b -= _colorChange;
	if (_color.b < .4f) _color.b = .4f;

	_lastRect = presence;

	_nav.move(presence);

	if (presence.x < 0.f)
	{
		presence.x = -presence.x;
		bounceHor(0);
	}
	if (presence.x > render->getScreenWidth() - presence.w)
	{
		presence.x = 2 * render->getScreenWidth() - presence.w - presence.x;
		bounceHor(0);
	}

	if (presence.y < 0.f)
	{
		presence.y = -presence.y;
		bounceVert(0);
	}
	if (presence.y > render->getScreenHeight() - presence.h)
	{
		//returnHome = true;
		//presence.y = 2 * render->getScreenHeight() - presence.h - presence.y;
		//bounceVert();
		gameOver = true;
	}
}

void Ball::draw()
{
	_pic.draw();
	_healthBar[0].draw();
	_healthBar[1].draw();

	realign();
}

void Ball::realign()
{
	_pic.setPosition(presence.x, presence.y);
	_pic.setSize(presence.w, presence.h);

	_healthBar[0].setPosition(presence.x, presence.y);
	_healthBar[0].setSize(presence.w, 5.f);
	_healthBar[1].setPosition(presence.x, presence.y);
	_healthBar[1].setSize(presence.w * ((float)_health / _maxHealth), 5.f);
}

void Ball::set()
{
	setPosition((render->getScreenWidth() / 2) - (presence.w / 2), render->getScreenHeight() - 75.f);
	_nav.vel = { 0.f, 0.f };
	_nav.acc = { 0.f, 0.f };
	isSet = true;
}

void Ball::launch(float horizontal)
{
	_nav.vel = { (float)cos((M_PI / 6) + (horizontal * (4 * M_PI / 6))), 1.65f };
	_nav.acc = { 0.f, -.0015f };
	isSet = false;
	_color.g += .6f;
	if (_color.g > 2.f) _color.g = 2.f;
}

void Ball::bounceVert(float extraDistance)
{
	_nav.vel.y = -_nav.vel.y;
	presence.y -= extraDistance *2;
	_color.r += .6f;
	if (_color.r > 2.f) _color.r = 2.f;
}

void Ball::bounceHor(float extraDistance)
{
	_nav.vel.x = -_nav.vel.x;
	presence.x -= extraDistance *2;
	_color.b += .6f;
	if (_color.b > 2.f) _color.b = 2.f;
}

void Ball::damage(int d)
{
	_health -= d;
	if (_health < 1) gameOver = true;
}

LineSeg Ball::getTrajectory(int corner)
{
	/*float bounds = presence.w;
	Vertex boundVector = presence.getMiddle();
	boundVector = { boundVector.x - _lastPos.x, boundVector.y - _lastPos.y };
	Vertex origin = { 0, 0 };
	float bvDist = distance(boundVector, origin);
	boundVector = { bounds * boundVector.x / bvDist, bounds * boundVector.y / bvDist };
	Vertex mid = presence.getMiddle();
	boundVector = { boundVector.x + mid.x, boundVector.y + mid.y };
	LineSeg s = { _lastPos, boundVector };*/
	LineSeg s = { _lastRect.getVertex(corner), presence.getVertex(corner) };
	return s;
}