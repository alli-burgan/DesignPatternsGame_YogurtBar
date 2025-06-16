//State Interface and Observer Subject
#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "GameStateObserver.h"

#define NUM_WIDTH 12
#define NUM_HEIGHT 30
#define NUM_OF_DIGITS 3

class Game;

class GameState {
public:
	GameState(SDL_Renderer* renderer, int score, int highScore);
	virtual ~GameState() {}

	virtual void Input() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	
	void LoadSprite();

	void RegisterObserver(GameStateObserver* observer);

	virtual void NotifyObservers() = 0;
	virtual void RenderScore() = 0;

protected:
	int mScore;
	int mHighScore;
	SDL_Texture* mTexture;
	const std::string mSpriteName = "SpriteSheet.png";
	SDL_Renderer* mRenderer;
	std::vector<GameStateObserver*> mObservers;
	bool mIsMouseDown;
	SDL_Point mMousePos;
	SDL_Point mClickOffset;
	const SDL_Rect mScreenRectangle = { 0,0,800,400 };
	const SDL_Rect mNumLocsOnSpriteSheet[10] = {
		{94,550,NUM_WIDTH, NUM_HEIGHT},  //0
		{115,550,NUM_WIDTH, NUM_HEIGHT}, //1
		{133,550,NUM_WIDTH, NUM_HEIGHT}, //2
		{156,550,NUM_WIDTH, NUM_HEIGHT}, //3
		{179,550,NUM_WIDTH, NUM_HEIGHT}, //4
		{200,550,NUM_WIDTH, NUM_HEIGHT}, //5
		{224,550,NUM_WIDTH, NUM_HEIGHT}, //6
		{247,550,NUM_WIDTH, NUM_HEIGHT}, //7
		{267,550,NUM_WIDTH, NUM_HEIGHT}, //8
		{292,550,NUM_WIDTH, NUM_HEIGHT}  //9
	};
private:
};