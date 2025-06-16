//Flyweight Factory Class of Flyweight Design Pattern
#pragma once
#include <stdio.h>
#include <string>
#include <unordered_map>

#include "FoodFlyweight.h"
#include <SDL.h>
#include <SDL_image.h>

class FoodFlyweightFactory {
public:
	FoodFlyweight* getFoodFlyweight(FoodTypes key, SDL_Texture* spriteSheet, SDL_Rect locationOnSpriteSheet, SDL_Renderer* renderer) {
		if (mFlyweights.find(key) == mFlyweights.end()) {
			mFlyweights[key] = new FoodFlyweight(spriteSheet, locationOnSpriteSheet, renderer);
		}
		return mFlyweights[key];
	}
	~FoodFlyweightFactory() {}
private:
	std::unordered_map<FoodTypes, FoodFlyweight*> mFlyweights;
};