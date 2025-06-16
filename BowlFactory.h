//This is a concrete creator class
#pragma once
#include "ItemInRecipeFactory.h"
#include "Bowl.h"
#include "ItemInRecipeFlyweight.h"
#include "iostream"

class BowlFactory : public ItemInRecipeFactory {
public:
	BowlFactory(ItemInRecipeFlyweight* flyweight) {
		mFlyweight = flyweight;
	}
	~BowlFactory() override {
		delete mFlyweight;
	}

	virtual ItemInRecipe* createItemInRecipe(SDL_Rect locOnScreen) override { 
		return new Bowl(mFlyweight, locOnScreen); 
	}
private:
};