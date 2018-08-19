#pragma once
#include "GameState.h"
#include "Bar.h"
#include "Ball.h"
#include "Tile.h"
#include "PauseScreen.h"
#include "GameOverScreen.h"
#include "Model.h"
#include "Light.h"

class EndlessState : public GameState
{
public:
	EndlessState();
	~EndlessState();
	StateEnum update();
	void draw();
	void drawUI();

private:	
	bool _paused;
	bool _gameOver;

	int fallSpace;
	Bar _bar[2];
	Ball _ball;

	PauseScreen _pauseScreen;
	GameOverScreen _gameOverScreen;

	std::vector<Tile> _tiles;
	int _tileW, _tileH;
	int _respawnTime;
	int _respawnTimer;

	Light _light[2];

	/*int _score;
	TextBox _scoreText;*/
};