#include "Orientor.h"

Orientor::Orientor()
{
	_pic[0].setColor(Color(white));
	_pic[0].setModel("cube");
	_pic[0].setTranslation(0, 0, 0);
	_pic[0].setScalar(.1f);

	//_pic[1].setColor(Color(red));
	_pic[1].setModel("dryad");
	_pic[1].setTxr("dryad");
	_pic[1].setTranslation(1.f, 0, 0);
	_pic[1].setScalar(.05f);

	_pic[2].setColor(Color(green));
	_pic[2].setModel("cuibe");
	_pic[2].setTranslation(0, 1.f, 0);
	_pic[2].setScalar(.1f);

	_pic[3].setColor(Color(yellow));
	_pic[3].setModel("cube");
	_pic[3].setTranslation(0, 0, 1.f);
	_pic[3].setScalar(.1f);
}

Orientor::~Orientor()
{
}

void Orientor::update()
{
	_pic[0].setRotation(float(sin(gameTimer.getTotal() / 300.f) * M_PI), 0, 0);
	_pic[1].setRotation(float(sin(gameTimer.getTotal() / 300.f) * M_PI), 0, 0);
	_pic[2].setRotation(float(sin(gameTimer.getTotal() / 300.f) * M_PI), 0, 0);
	_pic[3].setRotation(float(sin(gameTimer.getTotal() / 300.f) * M_PI), 0, 0);
}

void Orientor::draw()
{
	_pic[0].draw();
	_pic[1].draw();
	_pic[2].draw();
	_pic[3].draw();
}