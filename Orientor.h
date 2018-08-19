#pragma once
#include "Model.h"

class Orientor
{
public:
	Orientor();
	~Orientor();
	void update();
	void draw();

protected:
	Model _pic[4];
};

