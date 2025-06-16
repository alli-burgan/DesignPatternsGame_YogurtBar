//Concrete State of State Design Pattern
#include "StateInGame.h"
#include "Game.h"
#include "StateGameOver.h"

#include "stdio.h"
#include <iostream>

StateGameOver::StateGameOver(SDL_Renderer* renderer, int score, int highScore) : GameState(renderer, score, highScore) {}


void StateGameOver::Input() {
	SDL_Event event;
	SDL_Delay(10);
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_MOUSEBUTTONUP:
		mIsMouseDown = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		mIsMouseDown = true;
		break;
	case SDL_MOUSEMOTION:
		mMousePos = { event.motion.x, event.motion.y };
		break;
	}
}

void StateGameOver::Update() {
	if (mIsMouseDown) {
		if (SDL_PointInRect(&mMousePos, &mPlayAgainButton)) {
			NotifyObservers();
		}
	}
}

void StateGameOver::Render() {
	SDL_RenderClear(mRenderer);
	SDL_RenderCopy(mRenderer, mTexture, &mLocationOnSpriteSheet, &mScreenRectangle);
	RenderScore();
	SDL_RenderPresent(mRenderer);
}


void StateGameOver::NotifyObservers() {
	for (GameStateObserver* observer : mObservers) {
		observer->SetGameState(new StateInGame(mRenderer, 0, mHighScore));
	}
}

void StateGameOver::RenderScore() {
	int digit;
	SDL_Rect locOnScreen;
	for (int i = 0; i < NUM_OF_DIGITS; i++) {
		digit = (mScore / static_cast<int>(pow(10, (NUM_OF_DIGITS - i - 1))) % 10);
		locOnScreen = { 405 + ((i + 1) * 15),174,NUM_WIDTH, NUM_HEIGHT };
		SDL_RenderCopy(mRenderer, mTexture, &mNumLocsOnSpriteSheet[digit], &locOnScreen);
	}
	for (int i = 0; i < NUM_OF_DIGITS; i++) {
		digit = (mHighScore / static_cast<int>(pow(10, (NUM_OF_DIGITS - i - 1))) % 10);
		locOnScreen = { 405 + ((i + 1) * 15),214,NUM_WIDTH, NUM_HEIGHT };
		SDL_RenderCopy(mRenderer, mTexture, &mNumLocsOnSpriteSheet[digit], &locOnScreen);
	}
}
