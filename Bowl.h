//This is a concrete product class
#pragma once
#include "iostream"
#include "ItemInRecipe.h"
#include "ItemInRecipeFlyweight.h"
enum ItemInRecipeTypes;

class Bowl : public ItemInRecipe {
public:
	Bowl(ItemInRecipeFlyweight* flyweight, SDL_Rect locationOnScreen) : ItemInRecipe(flyweight, locationOnScreen, BOWL) {}
	~Bowl() override {}
	virtual void RenderItemInRecipe() override;
	virtual ItemInRecipe* CloneItemInRecipe() override;
private:
};