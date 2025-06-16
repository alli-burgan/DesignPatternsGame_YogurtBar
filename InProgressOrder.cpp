#include "InProgressOrder.h"

InProgressOrder::InProgressOrder(SDL_Rect locOnScreen) : mRecipeItems(0), mLocOnSpriteSheet({ 0,420,90,65 }), mLocOnScreen(locOnScreen) {}
void InProgressOrder::UpdateSprite() {
	if (mRecipeItems == 7) {
		mLocOnSpriteSheet = { 685, 505,90,65 };
	}
	else if (mRecipeItems == 5) {
		mLocOnSpriteSheet = { 580, 505,90,65 };
	}
	else if (mRecipeItems == 6) {
		mLocOnSpriteSheet = { 675, 427,90,65 };
	}
	else if (mRecipeItems == 4) {
		mLocOnSpriteSheet = { 580, 435,90,65 };
	}
	else {
		mLocOnSpriteSheet = { 0,420,90,65 };
	}
}

void InProgressOrder::Move(SDL_Rect newLocation) {
	mLocOnScreen.x = newLocation.x;
	mLocOnScreen.y = newLocation.y;
}

void InProgressOrder::Render(SDL_Renderer* renderer, SDL_Texture* texture) {
	SDL_RenderCopy(renderer, texture, &mLocOnSpriteSheet, &mLocOnScreen);
}