#include "Background.h"

Background::Background()
{
	_color = Color(white);

	setTxr("brown button");

	for (int w = 0; w < 3; w++)
	{
		for (int h = 0; h < 3; h++)
		{
			_clip[h * 3 + w].x = w / 3.f;
			_clip[h * 3 + w].y = h / 3.f;
			_clip[h * 3 + w].h = 1.f / 3.f;
			_clip[h * 3 + w].w = 1.f / 3.f;
			_piece[h * 3 + w].setClip(&_clip[h * 3 + w]);
		}
	}

	realign();
}

Background::~Background()
{
}

void Background::update()
{
}

void Background::draw()
{
	for (int i = 0; i < 9; i++)
	{
		_piece[i].draw();
	}
}

void Background::drawClipped(fRectangle clip)
{
	for (int i = 0; i < 9; i++)
	{
		_piece[i].drawClipped(clip);
	}
}

void Background::setPosition(GLfloat x, GLfloat y)
{
	presence.x = x;
	presence.y = y;
	realign();
}

void Background::setSize(GLfloat w, GLfloat h)
{
	presence.w = w;
	presence.h = h;
	realign();
}

void Background::setRGBA(Color c)
{
	_color = c;
	for (int i = 0; i < 9; i++)
	{
		_piece[i].setRGBA(c);
	}
}

void Background::setTxr(std::string txr)
{
	for (int i = 0; i < 9; i++)
	{
		_piece[i].setTexture(txr);
	}
}

void Background::realign()
{
	for (int w = 0; w < 3; w++)
	{
		for (int h = 0; h < 3; h++)
		{
			_piece[h * 3 + w].setPosition(presence.x + (presence.w * (w / 3.f)), presence.y + (presence.h * (h / 3.f)));
			_piece[h * 3 + w].setSize(presence.w / 3.f, presence.h / 3.f);
		}
	}
}