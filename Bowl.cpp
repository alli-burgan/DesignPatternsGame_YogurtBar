//Concrete Product Class of Factory Design Pattern
#include "Bowl.h"

void Bowl::RenderItemInRecipe() {
	if (mIsVisible) {
		SDL_RenderCopy(mFlyweight->mRenderer, mFlyweight->mTexture, &(mFlyweight->mLocOnSpriteSheet), &mLocationOnScreen);
	}
}
ItemInRecipe* Bowl::CloneItemInRecipe() {
	return new Bowl(*this);
}