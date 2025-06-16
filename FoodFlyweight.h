//Flyweight Class of Flyweight Design Pattern
#pragma once
#include <SDL.h>
#include <SDL_image.h>

enum FoodTypes {
	DEFAULT,
	YOGURT,
	STRAWBERRY,
	BLUEBERRY,
	BOWL
};

class FoodFlyweight {
public:
	FoodFlyweight(SDL_Texture* spriteSheet, SDL_Rect locationOnSpriteSheet, SDL_Renderer* renderer) :
		mTexture(spriteSheet), mLocOnSpriteSheet(locationOnSpriteSheet), mRenderer(renderer) {}
	~FoodFlyweight(){}
	SDL_Rect mLocOnSpriteSheet;
	SDL_Texture* mTexture;
	SDL_Renderer* mRenderer;
protected:
private:
};