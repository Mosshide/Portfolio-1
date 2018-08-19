#pragma once
#include "GameState.h"
#include "Bar.h"
#include "Ball.h"
#include "Tile.h"
#include "PauseScreen.h"
#include "GameOverScreen.h"
#include "Model.h"
#include "Light.h"

class ExplorationState : public GameState
{
public:
	ExplorationState();
	~ExplorationState();
	StateEnum update();
	void draw();
	void drawUI();

private:
	PauseScreen _pauseScreen;
	bool _paused;

	glm::vec3 _firstPersonCamera;

	Model _tree[100];
	Model _fern[1000];
	Model _ground[100];
};
