#include "PlayGame.h"

PlayGame::PlayGame()
{
	//Initialize all SDL subsystems
    SDL_Init(SDL_INIT_EVERYTHING);

	//init png code
	IMG_Init( IMG_INIT_PNG );

	//Initialize SDL_ttf
    TTF_Init();

	_quit = false;
	_borderQuit = false;
}

PlayGame::~PlayGame()
{
	delete _currentState;
	delete render;
	delete toyBox;

    //Quit SDL_ttf
    TTF_Quit();

	//Quit SDL_IMG
	IMG_Quit();

	//Quit SDL_mixer
    Mix_CloseAudio();

    //Quit SDL
    SDL_Quit();
}

void PlayGame::runGame()
{
	render = new Render;

	toyBox = new ToyBox;

	_border = new WindowBorder;

	gameCamera = new Camera;

	_currentState = new MainMenuState;

	UserInput input;

	while(!_quit && !_borderQuit)
	{
		gameTimer.update();

		_quit = input.getInput();

		_borderQuit = _border->update();

		_stateRequest = _currentState->update();
	
		toyBox->shader->bind();
		glEnable(GL_DEPTH_TEST);
		_currentState->draw();

		toyBox->uiShader->bind();
		glDisable(GL_DEPTH_TEST);
		_currentState->drawUI();
		_border->draw();

		render->renderGame();

		if (_stateRequest == quitState)
		{
			_quit = true;
		}
		else if (_stateRequest != _currentState->id)
		{
			delete _currentState;

			switch (_stateRequest)
			{
			case mainMenuState:
				_currentState = new MainMenuState;
				break;
			case endlessState:
				_currentState = new EndlessState;
				break;
			case explorationState:
				_currentState = new ExplorationState;
				break;
			}
		}
	}
}