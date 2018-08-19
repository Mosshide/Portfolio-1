#include "EndlessState.h"

EndlessState::EndlessState()
{
	id = endlessState;
	_paused = false;
	_gameOver = false;

	_ball.set();
	fallSpace = 100;
	_bar[0].setBounds( -(render->getScreenWidth() - fallSpace), render->getScreenWidth() - fallSpace, render->getScreenWidth() - fallSpace);
	_bar[0].reset();
	_bar[1].setBounds( fallSpace, (render->getScreenWidth() * 2) - fallSpace, render->getScreenWidth() - fallSpace);
	_bar[1].reset();

	_tileW = 15;
	_tileH = 6;
	for (int i = 0; i < _tileW; i++)
	{
		for (int ii = 0; ii < _tileH; ii++)
		{
			_tiles.push_back(Tile());
			_tiles.back().setPosition(75 + (render->getScreenWidth() - 100) * ((float)i / _tileW), 100.f + 40 * ii);
		}
	}
	_respawnTime = 500000;
	_respawnTimer = 0;
	
	_light[0].light = 0;
	_light[0].setPosition(glm::vec3(0, 4.f, 0));
	_light[0].setMagnitude(6.f);
	_light[1].light = 1;
	_light[1].setPosition(glm::vec3(4.f, 4.f, 0));
	_light[1].setMagnitude(4.f);

	/*_score = 0;
	_scoreText.setRGBA(Color(.4f, .4f, .4f, 1.f));
	_scoreText.setText("Score: " + std::to_string(_score));
	_scoreText.setPosition(10, 75);*/
}

EndlessState::~EndlessState()
{
}

StateEnum EndlessState::update()
{
	if (keyboard->getKey(escKey) == keyUp && !_gameOver) _paused = !_paused;

	if (_gameOver) _gameOverScreen.update();
	else if (_paused) _pauseScreen.update();
	else
	{
		_bar[0].update();
		_bar[1].update();
		_ball.update();

		if (_ball.gameOver)
		{
			_gameOver = true;
			_gameOverScreen.endGame(0);
		}

		//bar
		if (_ball.isSet)
		{
			if (_bar[0].vel != 0.f || keyboard->getKey(' ') == keyUp) _ball.launch((1 + rand() % 9) / 10.f);
		}
		else
		{
			float wratio = 0.f;
			for (int i = 0; i < 4; i++)
			{
				CollisionResult result = _bar[0].collision(_ball.getTrajectory(i), &wratio);
				if (result.collided == false) result = _bar[1].collision(_ball.getTrajectory(i), &wratio);
				if (result.collided == true)
				{
					if (result.side == 0 || result.side == 2) _ball.launch(wratio);
					else _ball.bounceHor(result.extraDistance.x);
					break;
				}
			}
		}

		//tiles
		for (int i = 0; i < _tileW * _tileH; i++)
		{
			_tiles[i].update();
			if (_tiles[i].alive)
			{
				for (int ii = 0; ii < 4; ii++)
				{
					CollisionResult result = _tiles[i].collision(_ball.getTrajectory(ii));
					if (result.collided == true)
					{
						_tiles[i].damage(_ball.attack);
						_ball.damage(1);
						/*_score++;
						_scoreText.setText("Score: " + std::to_string(_score));*/
						if (result.side == 0 || result.side == 2) _ball.bounceVert(result.extraDistance.y);
						else _ball.bounceHor(result.extraDistance.x);
						break;
					}
				}
			}
		}
		_respawnTimer += gameTimer.getDelta();
		if (_respawnTimer > _respawnTime)
		{
			_respawnTimer -= _respawnTime;
			int r = rand() % (_tileW * _tileH);
			if (!_tiles[r].alive) _tiles[r].reset();
		}

		//light
		GLfloat dist = 0;
		if (rayPlaneCollision(toyBox->shader->_cameraPos, mouse->worldRay, glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), &dist))
		{
			glm::vec3 target = toyBox->shader->_cameraPos + mouse->worldRay * dist;

			target += glm::vec3(0, 4.f, 0);

			_light[0].setPosition(target);
		}
	}

	if (_pauseScreen.quit || _gameOverScreen.quit) return mainMenuState;
	else return endlessState;
}

void EndlessState::draw()
{
	
}

void EndlessState::drawUI()
{
	_bar[0].draw();
	_bar[1].draw();
	_ball.draw();

	for (int i = 0; i < _tileW * _tileH; i++)
	{
		_tiles[i].draw();
	}

	/*_scoreText.draw();*/

	if (_gameOver) _gameOverScreen.draw();
	else if (_paused) _pauseScreen.draw();
}