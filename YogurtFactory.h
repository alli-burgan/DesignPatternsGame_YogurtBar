//This is a concrete creator class
#pragma once
#include "ItemInRecipeFactory.h"
#include "Yogurt.h"
#include "ItemInRecipeFlyweight.h"
#include "iostream"

class YogurtFactory : public ItemInRecipeFactory {
public:
	YogurtFactory(ItemInRecipeFlyweight* flyweight) {
		mFlyweight = flyweight;
	}
	~YogurtFactory() override {
		delete mFlyweight;
	}
	virtual ItemInRecipe* createItemInRecipe(SDL_Rect locOnScreen) override { 
		return new Yogurt(mFlyweight, locOnScreen); 
	}
private:
};