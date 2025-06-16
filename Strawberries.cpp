//Concrete Product Class of Factory Design Pattern
#include "Strawberries.h"

void Strawberries::RenderItemInRecipe() {
	if (mIsVisible) {
		SDL_RenderCopy(mFlyweight->mRenderer, mFlyweight->mTexture, &(mFlyweight->mLocOnSpriteSheet), &mLocationOnScreen);
	}
}
ItemInRecipe* Strawberries::CloneItemInRecipe() {
	return new Strawberries(*this);
}

