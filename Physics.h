#pragma once
#include <queue>
#include <cmath>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* timeeeeeeee */
#include "CollisionResult.h"
#include "fRectangle.h"
#include <chrono>
//#include "UserInput.h"

class Timer
{
public:
	Timer();
	~Timer();
	void update();
	Uint64 getTotal();
	Uint64 getDelta();
	float getMsDelta();

protected:
	Uint64 _totalTime;
	Uint64 _deltaTime;
	std::chrono::high_resolution_clock::time_point _oldTime;
	char _buffer[32];
}; 

extern Timer gameTimer;

/////////////
bool pointInRect(Vertex v, fRectangle *r);

bool pointInRect(Vertex v, fRectangle r);

bool rectCollison(fRectangle a, fRectangle b);

fRectangle rectIntersection(fRectangle a, fRectangle b);

float distanc3(V3rtex a, V3rtex b);

float distance(Vertex a, Vertex b);

float distance(SDL_Point a, SDL_Point b);

void getDirectedVelocity(Vertex a, Vertex b, GLfloat speed, Vertex &vel);

float getDirection(Vertex a, Vertex b);

void rotate(Vertex pivot, GLfloat angle, Vertex &point);

bool rayPlaneCollision(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3 pNormal, glm::vec3 pPoint, GLfloat *distance);

bool segIntersection(Vertex x, Vertex y, Vertex a, Vertex b, Vertex *i = nullptr);

bool segIntersection(LineSeg r, LineSeg s, Vertex *i = nullptr);