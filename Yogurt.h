//This is a concrete product class
#pragma once
#include "iostream"
#include "ItemInRecipe.h"
#include "ItemInRecipeFlyweight.h"
enum ItemInRecipeTypes;

class Yogurt : public ItemInRecipe {
public:
	Yogurt(ItemInRecipeFlyweight* flyweight, SDL_Rect locationOnScreen) : ItemInRecipe(flyweight, locationOnScreen, YOGURT) {}
	~Yogurt() override {}
	virtual void RenderItemInRecipe() override;
	virtual ItemInRecipe* CloneItemInRecipe() override;
private:
};