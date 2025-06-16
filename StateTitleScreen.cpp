//Concrete State of State Design Pattern
#include "StateTitleScreen.h"
#include "Game.h"
#include "StateInGame.h"
#include "stdio.h"
#include <iostream>

StateTitleScreen::StateTitleScreen(SDL_Renderer* renderer, int score, int highScore) : GameState(renderer, score, highScore) {}


void StateTitleScreen::Input() {
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

void StateTitleScreen::Update() {
	if (mIsMouseDown) {
		if (SDL_PointInRect(&mMousePos, &mPlayButton)) {
			NotifyObservers();
		}
	}
}

void StateTitleScreen::Render() {
	SDL_RenderClear(mRenderer);
	SDL_RenderCopy(mRenderer, mTexture, &mLocationOnSpriteSheet, &mScreenRectangle);
	RenderScore();
	SDL_RenderPresent(mRenderer);
}


void StateTitleScreen::NotifyObservers() {
	for (GameStateObserver* observer : mObservers) {
		observer->SetGameState(new StateInGame(mRenderer, 0, 0));
	}
}

void StateTitleScreen::RenderScore() {
	
}
