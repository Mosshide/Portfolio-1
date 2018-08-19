#include "Tile.h"

Tile::Tile()
{
	setSize(48, 16);
	setPosition(0, 0);

	_pic.setTexture("blank");
	_pic.setRGBA(Color(.4f, .4f, .4f, 1.f));

	_maxHealth = 2;
	_health = _maxHealth;

	alive = true;
}

Tile::~Tile()
{
}

void Tile::update()
{
	_pic.setRGBA(Color(.4f, .2f * _health, .2f * _health, 1.f));
}

void Tile::draw()
{
	if (alive) _pic.draw();
}

void Tile::realign()
{
	_pic.setPosition(presence.x, presence.y);
	_pic.setSize(presence.w, presence.h);
}

void Tile::reset()
{
	alive = true;
	_health = _maxHealth;
}

void Tile::damage(int d)
{
	_health -= d;
	if (_health < 1) alive = false;
}

CollisionResult Tile::collision(LineSeg l)
{
	Vertex ints[4];
	LineSeg s[4];

	int closest = -1;
	int closestd = INT_MAX;

	for (int i = 0; i < 4; i++)
	{
		s[i] = { presence.getVertex(i), presence.getVertex(i + 1) };
		if (segIntersection(l, s[i], &ints[i]))
		{
			int d = int(distance(l.a, ints[i]));
			if (d < closestd)
			{
				closest = i;
				closestd = d;
			}
		}
	}

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