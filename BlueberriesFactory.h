//Concrete Creator Class of Factory Design Pattern
#pragma once
#include "ItemInRecipeFactory.h"
#include "Blueberries.h"

class BlueberriesFactory : public ItemInRecipeFactory {
public:
	BlueberriesFactory(ItemInRecipeFlyweight* flyweight) {
		mFlyweight = flyweight;
	}
	~BlueberriesFactory() override {
		delete mFlyweight;
	}
	virtual ItemInRecipe* createItemInRecipe(SDL_Rect locOnScreen) override { 
		return new Blueberries(mFlyweight, locOnScreen); 
	}
private:
	ItemInRecipeFlyweight* mFlyweight;
};