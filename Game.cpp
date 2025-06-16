//Context of State Design Pattern and Concrete Observer of Observer Design Pattern
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "Game.h"
#include "StateTitleScreen.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400

Game::Game(){
	Init();
	mGameState = new StateTitleScreen(mRenderer, 0, 0);
	mGameState->RegisterObserver(this);
}

Game::~Game() {
	delete mGameState;
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
}

void Game::Input() {
	mGameState->Input();
}

void Game::Update() {
	mGameState->Update();
}

void Game::Render() {
	mGameState->Render();
}

void Game::SetGameState(GameState* nextGameState) {
	delete mGameState;
	mGameState = nextGameState;
	mGameState->RegisterObserver(this);
}

bool Game::Init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		mWindow = SDL_CreateWindow("Yogurt Bar", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (mWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (mRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}