#include "ExplorationState.h"

ExplorationState::ExplorationState()
{
	id = explorationState;

	SDL_SetWindowGrab(render->getWindow(), SDL_TRUE);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	//trees and ferns
	for (int i = 0; i < 100; i++)
	{
		_tree[i].setTxr("tree");
		_tree[i].setModel("tree");
		_tree[i].setTranslation((rand() % 1000) / 100.f - 5.f, 0, (rand() % 1000) / 100.f - 5.f);
		_tree[i].setRotation(0, (rand() % 1000) / 1000.0 * M_PI, 0);
		_tree[i].setScalar(.2f - (rand() % 1000) / 1000.0 * .1f);
	}
	for (int i = 0; i < 1000; i++)
	{
		_fern[i].setTxr("blank");
		_fern[i].setModel("fern");
		_fern[i].setColor(Color(green));
		_fern[i].setTranslation((rand() % 1000) / 100.f - 5.f, 0, (rand() % 1000) / 100.f - 5.f);
		_fern[i].setRotation(0, (rand() % 1000) / 1000.0 * M_PI, 0);
		_fern[i].setScalar(.1f - (rand() % 1000) / 1000.0 * .05f);
	}

	//ground
	for (int i = 0; i < 100; i++)
	{
		_ground[i].setTxr("blank");
		_ground[i].setModel("sprite");
		_ground[i].setColor(Color(brown, 1.f));
		_ground[i].setTranslation(1.f * (i / 10) - 50.f, 0, 1.f * (i % 10) - 50.f);
		_ground[i].setRotation(-M_PI / 2.f, 0, 0);
		_ground[i].setScalar(100.f);
	}
}

ExplorationState::~ExplorationState()
{
}

StateEnum ExplorationState::update()
{
	if (keyboard->getKey(escKey) == keyUp)
	{
		_paused = !_paused;
		if (_paused)
		{
			SDL_SetRelativeMouseMode(SDL_FALSE);
			SDL_SetWindowGrab(render->getWindow(), SDL_FALSE);
		}
		else 
		{
			SDL_SetWindowGrab(render->getWindow(), SDL_TRUE);
			SDL_SetRelativeMouseMode(SDL_TRUE);
		}
	}

	if (_paused) _pauseScreen.update();
	else
	{
		//fp
		//mouse->setPosition(render->getScreenWidth() / 2, render->getScreenHeight() / 2);

		toyBox->shader->rotateCamera(glm::vec3(mouse->dX / 100.f, mouse->dY / -100.f, 0));
		//toyBox->shader->setLight(toyBox->shader->_cameraPos + glm::vec3(0, 2, 0), 5.f, 0);

		float forwardVelocity = 0.f;
		float sideVelocity = 0.f;
		if (keyboard->getKey('w') == keyHold) forwardVelocity += .03f;
		if (keyboard->getKey('s') == keyHold) forwardVelocity -= .03f;
		if (keyboard->getKey('a') == keyHold) sideVelocity += .03f;
		if (keyboard->getKey('d') == keyHold) sideVelocity -= .03f;
		glm::vec3 front = toyBox->shader->_cameraFront;
		glm::vec3 right = glm::rotate(toyBox->shader->_cameraFront, (float)M_PI / 2, glm::vec3(0.f, 1.f, 0.f));
		GLfloat deltaX = (sideVelocity * right.x + forwardVelocity * front.x) * (toyBox->shader->_cameraPos.y / 2);
		GLfloat deltaZ = (sideVelocity * right.z + forwardVelocity * front.z) * (toyBox->shader->_cameraPos.y / 2);
		_firstPersonCamera.x += deltaX * (gameTimer.getDelta() / 2000.f);
		_firstPersonCamera.z += deltaZ * (gameTimer.getDelta() / 2000.f);

		_firstPersonCamera.y -= .01f;
		if (_firstPersonCamera.y < .2f) _firstPersonCamera.y = .2f;

		toyBox->shader->setCameraTranslate(_firstPersonCamera);
		toyBox->shader->setLight(toyBox->shader->_cameraPos, 2.f);// +glm::vec3(0, 2, 0));

		//light
		/*GLfloat dist = 0;
		if (rayPlaneCollision(toyBox->shader->_cameraPos, mouse->worldRay, glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), &dist))
		{
			glm::vec3 target = toyBox->shader->_cameraPos + mouse->worldRay * dist;

			target += glm::vec3(0, 4.f, 0);

			_light[0].setPosition(target);
		}*/
	}

	if (_pauseScreen.quit)
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		SDL_SetWindowGrab(render->getWindow(), SDL_FALSE);
		return mainMenuState;
	}
	else return explorationState;
}

void ExplorationState::draw()
{
	for (int i = 0; i < 100; i++)
	{
		_tree[i].draw();
		_ground[i].draw();
	}
	for (int i = 0; i < 1000; i++)
	{
		_fern[i].draw();
	}
}

void ExplorationState::drawUI()
{
	if (_paused) _pauseScreen.draw();
}