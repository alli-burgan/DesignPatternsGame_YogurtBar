//Flyweight Factory Class of Flyweight Design Pattern
#pragma once
#include <stdio.h>
#include <string>
#include <unordered_map>

#include "ItemInRecipeFlyweight.h"
#include <SDL.h>
#include <SDL_image.h>

class ItemInRecipeFlyweightFactory {
public:
	ItemInRecipeFlyweight* getItemInRecipeFlyweight(ItemInRecipeTypes key, SDL_Texture* spriteSheet, SDL_Rect locationOnSpriteSheet, SDL_Renderer* renderer) {
		if (mFlyweights.find(key) == mFlyweights.end()) {
			mFlyweights[key] = new ItemInRecipeFlyweight(spriteSheet, locationOnSpriteSheet, renderer);
		}
		return mFlyweights[key];
	}
	~ItemInRecipeFlyweightFactory() {}
private:
	std::unordered_map<ItemInRecipeTypes, ItemInRecipeFlyweight*> mFlyweights;
};