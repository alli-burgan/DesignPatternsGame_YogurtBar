#include "GameState.h"

GameState::GameState(SDL_Renderer* renderer, int score, int highScore) : mRenderer(renderer), mTexture(NULL), mScore(score), mHighScore(highScore){
	LoadSprite();
}

void GameState::LoadSprite() {
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(mSpriteName.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", mSpriteName.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", mSpriteName.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
}

void GameState::RegisterObserver(GameStateObserver* observer) {
	mObservers.push_back(observer);
}

