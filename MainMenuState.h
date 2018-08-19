#pragma once
#include "Button.h"
#include "GameState.h"
#include "toyBox.h"
#include "Camera.h"
#include "Orientor.h"
#include "Light.h"

class MainMenuState : public GameState
{
public:
	MainMenuState();
	~MainMenuState();
	StateEnum update();
	void draw();
	void drawUI();

private:
	//Orientor _ori;
	Button _startButton;
	Button _FPButton;
	Model _title;
	Light _light;
	//GLfloat _lightHeight;

	//UIText _debugPos;
};