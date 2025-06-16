//This class is the orders that the user is building
#pragma once
#include <SDL.h>
#include <SDL_image.h>

enum BitShiftValues {
	STRAWBERRYBIT,
	BLUEBERRYBIT,
	YOGURTBIT
};

class InProgressOrder {
public:
	InProgressOrder(SDL_Rect locOnScreen);

	void UpdateSprite();

	void Move(SDL_Rect newLocation);

	void Render(SDL_Renderer* renderer, SDL_Texture* texture);

	int mRecipeItems;
	SDL_Rect mLocOnSpriteSheet;
	SDL_Rect mLocOnScreen;
};