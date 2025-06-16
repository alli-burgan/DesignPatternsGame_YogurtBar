//Concrete State of State Design Pattern
#pragma once
#include "GameState.h"
#include <SDL.h>
#include <SDL_image.h>
#include "ItemInRecipeFactory.h"
#include "StrawberriesFactory.h"
#include "BlueberriesFactory.h"
#include "YogurtFactory.h"
#include "BowlFactory.h"
#include "InProgressOrder.h"
#include "Order.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400
#define INPUT_DELAY 10
#define BOWL_WIDTH 60
#define BOWL_HEIGHT 35
#define ORDER_WIDTH 50
#define ORDER_HEIGHT 50
#define MAX_NUM_OF_ORDERS 5
#define DISTANCE_BETWEEN_ORDER_CARDS 10
#define GAME_TIMER 120

struct Tray {
	Order* attemptedOrder;
	InProgressOrder* attemptedInProgressOrder;
};

class StateInGame : public GameState {
public:
	StateInGame(SDL_Renderer* renderer, int score, int highScore);
	~StateInGame() override;
	virtual void Input() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void NotifyObservers() override;
	void CreateFridgeItemInRecipe();
	void GenerateOrder();
	virtual void RenderScore() override;
	void RenderScoreBackground();
	void RenderTimeLeft();
private:
	bool mJustDroppedItemInRecipe;
	bool mJustDroppedOrder;
	bool mJustDroppedInProgressOrder;
	Uint32 mStartTime;
	Uint32 mGameTime;
	ItemInRecipeFlyweightFactory* mFlyweightFactory;
	ItemInRecipeFactory* mStrawberriesFactory;
	ItemInRecipeFactory* mBlueberriesFactory;
	ItemInRecipeFactory* mYogurtFactory;
	ItemInRecipeFactory* mBowlFactory;
	std::vector<ItemInRecipe*> mAllItemsInRecipe;
	ItemInRecipe* mSelectedItemInRecipe;
	InProgressOrder* mSelectedInProgressOrder;
	std::vector<Order*> mAllOrders;
	Order* mSelectedOrder;
	const SDL_Rect mBackgroundSpriteRectangle = { 5,0,795,395 };
	std::vector<InProgressOrder*> mAllInProgressOrders;
	const SDL_Rect mOrderTurnInLocation = { 640,302,40,50 };
	const SDL_Rect mTrayLocation = { 565,300,90,60 };
	Tray mTray;
	SDL_Rect mReplacementOrderLocation = { 0, 5, ORDER_WIDTH, ORDER_HEIGHT };
};
