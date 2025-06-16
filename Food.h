//Abstract Product Class of Factory Design Pattern
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Receiver.h"

class FoodFlyweight;
enum FoodTypes;

class Food : public Receiver {
public:
	Food(FoodFlyweight* flyweight, SDL_Rect locationOnScreen, FoodTypes foodType) : mIsVisible(false), mLocationOnScreen(locationOnScreen), mFlyweight(flyweight), mFoodType(foodType) {}
	virtual ~Food() {}
	virtual void RenderFood()=0;
	virtual void PerformAction(SDL_Rect newLocation) override {
		mLocationOnScreen.x = newLocation.x;
		mLocationOnScreen.y = newLocation.y;
	}
	virtual Food* CloneFood() = 0;
	void SetVisibility(bool isVisible) {
		mIsVisible = isVisible;
	}
	SDL_Rect mLocationOnScreen;
	FoodTypes mFoodType;
protected:
	bool mIsVisible;
	FoodFlyweight* mFlyweight;
};