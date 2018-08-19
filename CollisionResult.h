#pragma once
#include "Vertex.h"

struct CollisionResult
{
	bool collided;
	Vertex point;
	LineSeg lineSeg;
	int side;
	Vertex extraDistance;
};