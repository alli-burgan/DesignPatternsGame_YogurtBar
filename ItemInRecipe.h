//Abstract Product Class of Factory Design Pattern
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Receiver.h"

class ItemInRecipeFlyweight;
enum ItemInRecipeTypes;

class ItemInRecipe : public Receiver {
public:
	ItemInRecipe(ItemInRecipeFlyweight* flyweight, SDL_Rect locationOnScreen, ItemInRecipeTypes foodType) : mIsVisible(false), mLocationOnScreen(locationOnScreen), mFlyweight(flyweight), mItemInRecipeType(foodType) {}
	virtual ~ItemInRecipe() {}
	virtual void RenderItemInRecipe()=0;
	virtual void PerformAction(SDL_Rect newLocation) override {
		mLocationOnScreen.x = newLocation.x;
		mLocationOnScreen.y = newLocation.y;
	}
	virtual ItemInRecipe* CloneItemInRecipe() = 0;
	void SetVisibility(bool isVisible) {
		mIsVisible = isVisible;
	}
	SDL_Rect mLocationOnScreen;
	ItemInRecipeTypes mItemInRecipeType;
protected:
	bool mIsVisible;
	ItemInRecipeFlyweight* mFlyweight;
};