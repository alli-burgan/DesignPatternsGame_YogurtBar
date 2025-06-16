//Concrete Product Class of Factory Design Pattern
#pragma once
#include "iostream"
#include "ItemInRecipeFlyweight.h"
#include "ItemInRecipe.h"
enum ItemInRecipeTypes;

class Blueberries : public ItemInRecipe {
public:	
	Blueberries(ItemInRecipeFlyweight* flyweight, SDL_Rect locationOnScreen) : ItemInRecipe(flyweight, locationOnScreen, BLUEBERRY) {}
	~Blueberries()override {}
	virtual void RenderItemInRecipe() override;
	virtual ItemInRecipe* CloneItemInRecipe() override;
private:
};