#pragma once
#include "UserInput.h"
#include "Physics.h"
#include "StateEnum.h"
#include "AllStates.h"
#include "WindowBorder.h"
#include <SDL_thread.h>

class PlayGame
{
public:
	PlayGame();
	~PlayGame();
	void runGame();

private:
	StateEnum _stateRequest;
	GameState *_currentState;
	WindowBorder *_border;
	bool _quit;
	bool _borderQuit;
};