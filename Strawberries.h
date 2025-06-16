//Concrete Product Class of Factory Design Pattern
#pragma once
#include "iostream"

#include "ItemInRecipe.h"
#include "ItemInRecipeFlyweightFactory.h"
class ItemInRecipeFlyweight;
enum ItemInRecipeTypes;

class Strawberries : public ItemInRecipe {
public:
	Strawberries(ItemInRecipeFlyweight* flyweight, SDL_Rect locationOnScreen) : ItemInRecipe(flyweight, locationOnScreen, STRAWBERRY) {}
	~Strawberries() override {}
	virtual void RenderItemInRecipe() override;
	virtual ItemInRecipe* CloneItemInRecipe() override;
private:
};