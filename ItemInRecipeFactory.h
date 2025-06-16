//Abstract Creator Class of Factory Design Pattern
#pragma once
#include "ItemInRecipe.h"


class ItemInRecipeFactory {
public:
	virtual ItemInRecipe* createItemInRecipe(SDL_Rect locOnScreen) = 0;
	virtual ~ItemInRecipeFactory() {}
protected:
	ItemInRecipeFlyweight* mFlyweight;
};