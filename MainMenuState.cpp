#include "MainMenuState.h"

MainMenuState::MainMenuState()
{
	id = mainMenuState;

	//gameCamera->set(0, 50, 0);

	_startButton.setText("Start");
	_startButton.setPosition(render->getScreenWidth() / 2 - 100, render->getScreenHeight() - 100);
	//_startButton.setPosition(0, 0);
	_startButton.setRGBA(Color(.8f, .8f, .8f, 1.f));
	_startButton.setFont(2);

	_FPButton.setText("Start FP");
	_FPButton.setPosition(0, render->getScreenHeight() - 100);
	//_FPButton.setRGBA(Color(.8f, .8f, .8f, 1.f));
	_FPButton.setFont(2);
	_FPButton.setBackgroundTxr("brown button");

	_title.setTxr("title");
	_title.setModel("sprite");
	_title.setTranslation(0, 0, 0);
	_title.setRotation(float(M_PI / 2), float(M_PI), 0);
	//_title.setRotation(float(M_PI / 2), glm::vec3(0, 0, 1));
	_title.setScalar(3);

	//_debugPos.setText("0, 0, 0");
	//_debugPos.setPosition(50, 50);

	_light.setPosition(glm::vec3(0, 3000.f, 0));
	_light.setMagnitude(4000.f);
}

MainMenuState::~MainMenuState()
{
}

StateEnum MainMenuState::update()
{
	//_ori.update();

	_startButton.update();
	_FPButton.update();

	/*GLfloat dist = 0;
	if (rayPlaneCollision(toyBox->shader->_cameraPos, mouse->worldRay, glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), &dist))
	{
		glm::vec3 target = toyBox->shader->_cameraPos + mouse->worldRay * dist;

		if (mouse->wheel != 0.f) _lightHeight += mouse->wheel / 10.f;
		target += glm::vec3(0, _lightHeight, 0);

		_light.setPosition(target);

		_debugPos.setText(std::to_string(target.x) + "," + std::to_string(target.y) + "," + std::to_string(target.z));
	}*/

	if (_startButton.getClick(leftClick) == clickUp) return endlessState;
	else if (_FPButton.getClick(leftClick) == clickUp) return explorationState;
	else return mainMenuState;
}

void MainMenuState::draw()
{
	//_ori.draw();

	_title.draw();

	//_light.draw();
}

void MainMenuState::drawUI()
{
	_startButton.draw();
	_FPButton.draw();

	//_debugPos.draw();
}