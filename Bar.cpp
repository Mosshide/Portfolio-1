#include "Bar.h"

Bar::Bar()
{
	_pic.setTexture("blank");
	_pic.setRGBA(Color(.4f, .4f, .4f, 1.f));
	presence = fRectangle(render->getScreenWidth() / 2 - 100, render->getScreenHeight() - 40, 200, 15);

	bound[0] = 0;
	bound[1] = render->getScreenWidth();

	vel = 0.f;

	realign();
}

Bar::~Bar()
{
}

void Bar::update()
{
	vel = 0.f;
	if (keyboard->getKey('d') == keyHold) vel += 1.5f;
	if (keyboard->getKey('a') == keyHold) vel -= 1.5f;
	offsetPosition(gameTimer.getMsDelta() * vel, 0.f);

	if (presence.x < bound[0]) presence.x = float(bound[0]);
	if (presence.x > bound[1] - presence.w) presence.x = float(bound[1] - presence.w);

	realign();
}

void Bar::draw()
{
	_pic.draw();
}

void Bar::realign()
{
	_pic.setPosition(presence.x, presence.y);
	_pic.setSize(presence.w, presence.h);
}

void Bar::setBounds(int a, int b, int w)
{
	bound[0] = a;
	bound[1] = b;
	presence.w = float(w);
}

void Bar::reset()
{
	presence.x = bound[0] + ((bound[1] - presence.w - bound[0]) / 2);
}

CollisionResult Bar::collision(LineSeg l, float *wratio)
{
	Vertex ints[4];
	LineSeg s[4];

	int closest = -1;
	float closestd = FLT_MAX;

	for (int i = 0; i < 4; i++)
	{
		s[i] = { presence.getVertex(i), presence.getVertex(i + 1) };
		if (segIntersection(l, s[i], &ints[i]))
		{
			float d = distance(l.a, ints[i]);
			if (d < closestd)
			{
				closest = i;
				closestd = d;
			}
		}
	}

	if (wratio != nullptr) *wratio = (ints[closest].x - presence.x) / presence.w;

	Vertex extra = { 0, 0 };
	CollisionResult c;
	if (closest == -1) c = { false, ints[0], s[0], 0, extra };
	else
	{
		extra = { l.b.x - ints[closest].x, l.b.y - ints[closest].y };
		c = { true, ints[closest], s[closest], closest, extra };
	}
	return c;
}