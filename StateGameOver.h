//Concrete State of State Design Pattern
#pragma once
#include "GameState.h"

class StateGameOver : public GameState {
public:
	StateGameOver(SDL_Renderer* renderer, int score, int highScore);
	virtual void Input() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void NotifyObservers() override;
	virtual void RenderScore() override;

private:
	const SDL_Rect mPlayAgainButton = { 310,250,170,55 };
	const SDL_Rect mLocationOnSpriteSheet = { 0,1026,795,400 };
};