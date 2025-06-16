//Concrete Observer Class of Observer Design Pattern
#pragma once
#include "GameState.h"

#include <SDL.h>
#include <SDL_image.h>

class Game : public GameStateObserver {
public:
	Game();
	~Game();

	virtual void SetGameState(GameState* nextGameState);

	bool Init();

	void Input();
	void Update();
	void Render();

	SDL_Renderer* mRenderer;

private:
	GameState* mGameState;
	SDL_Window* mWindow;	
};