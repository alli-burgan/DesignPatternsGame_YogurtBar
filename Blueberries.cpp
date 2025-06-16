//Concrete Product Class of Factory Design Pattern
#include "Blueberries.h"

void Blueberries::RenderItemInRecipe() {
	if (mIsVisible) {
		SDL_RenderCopy(mFlyweight->mRenderer, mFlyweight->mTexture, &(mFlyweight->mLocOnSpriteSheet), &mLocationOnScreen);
	}
}
ItemInRecipe* Blueberries::CloneItemInRecipe() {
	return new Blueberries(*this);
}