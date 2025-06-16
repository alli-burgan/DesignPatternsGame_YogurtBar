#pragma once
#include <SDL.h>
#include <SDL_image.h>

#define ORDER_TIME 35
class Order {
public:
	Order(SDL_Rect locOnScreen, int orderItems);
		
	void RenderOrders(SDL_Renderer* renderer, SDL_Texture* texture);
	void MoveOrders(SDL_Rect newLocation);
	bool UpdateOrderTimer(Uint32 gameTime);
	void RenderOrderTimer(SDL_Renderer* renderer);
	SDL_Rect mLocOnScreen;
	SDL_Rect mOriginalLocOnScreen;
	int mOrderItems;
	Uint32 mOrderStartTime;
	int mTimeLeft;
private:
	SDL_Rect mLocOnSpriteSheet;
};