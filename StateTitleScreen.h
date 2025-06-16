#pragma once
#include "GameState.h"

class StateTitleScreen : public GameState {
public:
	StateTitleScreen(SDL_Renderer* renderer, int score, int highScore);
	virtual ~StateTitleScreen() {}

	virtual void Input() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void NotifyObservers() override;
	virtual void RenderScore() override;
private:
	const SDL_Rect mPlayButton = { 305,324,165,60 };
	const SDL_Rect mLocationOnSpriteSheet = { 0,610,795,400 };
};