//Concrete Creator Class of Factory Design Pattern

#pragma once
#include "ItemInRecipeFactory.h"
#include "Strawberries.h"
#include "ItemInRecipeFlyweight.h"
#include "iostream"

class StrawberriesFactory : public ItemInRecipeFactory {
public:
	StrawberriesFactory(ItemInRecipeFlyweight* flyweight) {
		mFlyweight = flyweight;
	}
	~StrawberriesFactory() override {
		delete mFlyweight;
	}
	virtual ItemInRecipe* createItemInRecipe(SDL_Rect locOnScreen) override { 
		return new Strawberries(mFlyweight, locOnScreen); 
	}
private:
	
};