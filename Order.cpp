#include "Order.h"

Order::Order(SDL_Rect locOnScreen, int orderItems) : mLocOnScreen(locOnScreen), mOrderItems(orderItems), mOriginalLocOnScreen(locOnScreen), mOrderStartTime(SDL_GetTicks()), mTimeLeft(ORDER_TIME) {
	if (mOrderItems == 3) { //11 both
		mLocOnSpriteSheet.x = 105;
	}
	else if (mOrderItems == 1) { //1 strawberries
		mLocOnSpriteSheet.x = 205;
	}
	else if (mOrderItems == 2) {//10 blueberries
		mLocOnSpriteSheet.x = 305;
	}
	mLocOnSpriteSheet.y = 400;
	mLocOnSpriteSheet.w = 88;
	mLocOnSpriteSheet.h = 100;
}
void Order::RenderOrders(SDL_Renderer* renderer, SDL_Texture* texture) {
	SDL_RenderCopy(renderer, texture, &mLocOnSpriteSheet, &mLocOnScreen);
}
void Order::MoveOrders(SDL_Rect newLocation) {
	mLocOnScreen.x = newLocation.x;
	mLocOnScreen.y = newLocation.y;
}

/// <summary>
/// updates the order's time left
/// </summary>
/// <param name="timePassed">sent the game time</param>
/// <returns>returns true if order is valid, false it time has run out</returns>
bool Order::UpdateOrderTimer(Uint32 gameTime) {
	mTimeLeft = ORDER_TIME - ((gameTime - mOrderStartTime) / 1000);
	if (mTimeLeft < 0) {
		return false;
	}
	return true;
}

void Order::RenderOrderTimer(SDL_Renderer* renderer) {
	if (mTimeLeft > 25) {
		//render a green rectangle
		SDL_SetRenderDrawColor(renderer, 0x0, 0xFF, 0x0, 0xFF);
	}
	else if (mTimeLeft > 10) {
		//render a yellow rectangle
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x0, 0xFF);
	}
	else {
		//render a red rectangle
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, 0xFF);
	}

	SDL_Rect locOnScreen;// = mOriginalLocOnScreen;
	locOnScreen.x = mOriginalLocOnScreen.x + 5;
	locOnScreen.y = mOriginalLocOnScreen.h + 5;
	locOnScreen.h = 5;
	locOnScreen.w = static_cast<int>(mTimeLeft*1.2);
	
	SDL_RenderFillRect(renderer, &locOnScreen);
}
