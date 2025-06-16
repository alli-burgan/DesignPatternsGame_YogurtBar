//Concrete Product Class of Factory Design Pattern
#include "Yogurt.h"

void Yogurt::RenderItemInRecipe() {
	if (mIsVisible) {
		SDL_RenderCopy(mFlyweight->mRenderer, mFlyweight->mTexture, &(mFlyweight->mLocOnSpriteSheet), &mLocationOnScreen);
	}
}
ItemInRecipe* Yogurt::CloneItemInRecipe() {
	return new Yogurt(*this);
}