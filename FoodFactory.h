//Abstract Creator Class of Factory Design Pattern
#pragma once
#include "Food.h"


class FoodFactory {
public:
	virtual FoodFactory* createFood(SDL_Rect locOnScreen) = 0;
	virtual ~FoodFactory() {}
protected:
	FoodFactory* mFlyweight;
};