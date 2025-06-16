//Concrete State of State Design Pattern
#include <SDL.h>
#include <SDL_image.h>
#include "stdio.h"
#include <iostream>

#include "StateInGame.h"
#include "Game.h"
#include "StateGameOver.h"
#include "Invoker.h"
#include "MoveCommand.h"



StateInGame::StateInGame(SDL_Renderer* renderer, int score, int highScore) : GameState(renderer, score, highScore), mStartTime(SDL_GetTicks()), mGameTime(SDL_GetTicks()), mFlyweightFactory(new ItemInRecipeFlyweightFactory()), mJustDroppedItemInRecipe(false) {
	CreateFridgeItemInRecipe();
	srand(time(0));
	for (int count = 0; count < MAX_NUM_OF_ORDERS; count++) {
		GenerateOrder();
	}
}

StateInGame::~StateInGame() {
	delete mFlyweightFactory;
	delete mStrawberriesFactory;
	delete mBlueberriesFactory;
	delete mYogurtFactory;
	delete mBowlFactory;
	for (ItemInRecipe* food : mAllItemsInRecipe) {
		delete food;
	}
	for (InProgressOrder* inProgressOrder : mAllInProgressOrders) {
		delete inProgressOrder;
	}
	for (Order* order : mAllOrders) {
		delete order;
	}
}

void StateInGame::Input() {
	SDL_Event event;
	SDL_Delay(INPUT_DELAY);
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_MOUSEBUTTONUP:
		mIsMouseDown = false;
		if (mSelectedItemInRecipe) {
			mJustDroppedItemInRecipe = true;
		}
		if (mSelectedOrder) {
			mJustDroppedOrder = true;
		}
		if (mSelectedInProgressOrder) {
			mJustDroppedInProgressOrder = true;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		mIsMouseDown = true;
		break;
	case SDL_MOUSEMOTION:
		mMousePos = { event.motion.x, event.motion.y };
		break;
	}
}

void StateInGame::Update() {
	mGameTime = SDL_GetTicks(); //comment this line to test without time limit
	//This checks if the game has been running for GAME_TIMER seconds. If so, it ends the game.
	if (mStartTime + GAME_TIMER*1000 < mGameTime) {
		if (mScore > mHighScore) {
			mHighScore = mScore;
		}
		NotifyObservers();
	}
	else {
		//check each order to see if its time is up
		//if its time is up, delete it from the list of orders and subtract from the score
		for (int index = 0; index < mAllOrders.size(); index++) {
			if (!mAllOrders.at(index)->UpdateOrderTimer(mGameTime)) {
				mReplacementOrderLocation = mAllOrders.at(index)->mOriginalLocOnScreen;
				if (mTray.attemptedOrder == mAllOrders.at(index)) {
					mTray.attemptedOrder = NULL;
				}
				delete mAllOrders.at(index);
				mAllOrders.erase(mAllOrders.begin() + index);
				if (mScore - 5 > 0) {
					mScore = mScore - 5;
				}
				break;
			}
		}
		//if the tray has an order and an order card
		if (mTray.attemptedInProgressOrder && mTray.attemptedOrder) {
			// Check if the order is right (both least significant bits are the same)
			if (((mTray.attemptedInProgressOrder->mRecipeItems & 1) == (mTray.attemptedOrder->mOrderItems & 1)) && (((mTray.attemptedInProgressOrder->mRecipeItems >> 1) & 1) == ((mTray.attemptedOrder->mOrderItems >> 1) & 1))) {
				//add points based on amount of time left on order
				if (mTray.attemptedOrder->mTimeLeft > 25) {
					mScore += 25; 
				}
				else if (mTray.attemptedOrder->mTimeLeft > 10) {
					mScore += 20;
				}
				else {
					mScore += 15;
				}
				//delete order card
				for (int index = 0; index < mAllOrders.size(); index++) {
					if (mAllOrders.at(index) == mTray.attemptedOrder) {
						mReplacementOrderLocation = mAllOrders.at(index)->mOriginalLocOnScreen;
						delete mAllOrders.at(index);
						mAllOrders.erase(mAllOrders.begin() + index);
						break;
					}
				}
				//delete the in progress order
				for (int index = 0; index < mAllOrders.size(); index++) {
					if (mAllInProgressOrders.at(index) == mTray.attemptedInProgressOrder) {
						delete mAllInProgressOrders.at(index);
						mAllInProgressOrders.erase(mAllInProgressOrders.begin() + index);
						break;
					}
				}
			}
			else { //the user submitted an incorrect order
				//subtract points
				if (mScore - 10 >= 0) {
					mScore -= 10;
				}
				//move the order card back to its original location
				mTray.attemptedOrder->mLocOnScreen = mTray.attemptedOrder->mOriginalLocOnScreen;
				//find and delete the in progress order that they tried to submit
				for (int index = 0; index < mAllOrders.size(); index++) {
					if (mAllInProgressOrders.at(index) == mTray.attemptedInProgressOrder) {
						delete mAllInProgressOrders.at(index);
						mAllInProgressOrders.erase(mAllInProgressOrders.begin() + index);
						break;
					}
				}
			}
			mTray.attemptedInProgressOrder = NULL;
			mTray.attemptedOrder = NULL;
		}

		while(mAllOrders.size() < MAX_NUM_OF_ORDERS){
			GenerateOrder();
		}

		if (mIsMouseDown && mSelectedItemInRecipe) { // if the mouse is down and on a food
			//make a command that moves the food
			SDL_Rect newLocation = { mMousePos.x - mClickOffset.x ,mMousePos.y - mClickOffset.y, mSelectedItemInRecipe->mLocationOnScreen.w, mSelectedItemInRecipe->mLocationOnScreen.h };
			MoveCommand* command = new MoveCommand(mSelectedItemInRecipe, newLocation);
			Invoker invoker;
			invoker.SetCommand(command);
			invoker.ExecuteCommand();
			delete command;
		}
		else if (mIsMouseDown && mSelectedInProgressOrder) { // if the mouse is down and on a food
			SDL_Rect newLocation = { mMousePos.x - mClickOffset.x ,mMousePos.y - mClickOffset.y, mSelectedInProgressOrder->mLocOnScreen.w, mSelectedInProgressOrder->mLocOnScreen.h };
			mSelectedInProgressOrder->Move(newLocation);
		}
		else if (mIsMouseDown && mSelectedOrder) { // if the mouse is down and on a food
			SDL_Rect newLocation = { mMousePos.x - mClickOffset.x ,mMousePos.y - mClickOffset.y, mSelectedOrder->mLocOnScreen.w, mSelectedOrder->mLocOnScreen.h };
			mSelectedOrder->MoveOrders(newLocation);
		}
		else if (mIsMouseDown) {
			//check to see if it is on a food. if so, set selected food
			for (ItemInRecipe* food : mAllItemsInRecipe) {
				if (SDL_PointInRect(&mMousePos, &food->mLocationOnScreen)) {
					mSelectedItemInRecipe = food->CloneItemInRecipe();

					if (mSelectedItemInRecipe->mItemInRecipeType == BOWL) {
						mSelectedItemInRecipe->mLocationOnScreen = { static_cast<int>(mMousePos.x - .5 * (BOWL_WIDTH)), static_cast<int>(mMousePos.y - .5 * (BOWL_HEIGHT)), BOWL_WIDTH, BOWL_HEIGHT };
					}
					else if (mSelectedItemInRecipe->mItemInRecipeType == YOGURT) {
						mSelectedItemInRecipe->mLocationOnScreen.y = static_cast<int>(mMousePos.y-35);
					}
					mSelectedItemInRecipe->SetVisibility(true);
					mAllItemsInRecipe.push_back(mSelectedItemInRecipe);
					mClickOffset.x = mMousePos.x - mSelectedItemInRecipe->mLocationOnScreen.x;
					mClickOffset.y = mMousePos.y - mSelectedItemInRecipe->mLocationOnScreen.y;
				}
			}
			for (InProgressOrder* inProgressOrder : mAllInProgressOrders) {
				if (SDL_PointInRect(&mMousePos, &inProgressOrder->mLocOnScreen)) {
					mSelectedInProgressOrder = inProgressOrder;
					mClickOffset.x = mMousePos.x - mSelectedInProgressOrder->mLocOnScreen.x;
					mClickOffset.y = mMousePos.y - mSelectedInProgressOrder->mLocOnScreen.y;
				}
			}
			for (Order* order : mAllOrders) {
				if (SDL_PointInRect(&mMousePos, &order->mLocOnScreen)) {
					mSelectedOrder = order;
					mClickOffset.x = mMousePos.x - mSelectedOrder->mLocOnScreen.x;
					mClickOffset.y = mMousePos.y - mSelectedOrder->mLocOnScreen.y;
				}
			}
		}
		else if (mJustDroppedItemInRecipe) {
			if (mSelectedItemInRecipe->mItemInRecipeType == BOWL) {
				mAllInProgressOrders.push_back(new InProgressOrder(mSelectedItemInRecipe->mLocationOnScreen));
			}
			else {
				for (InProgressOrder* inProgressOrder : mAllInProgressOrders) {
					if (SDL_PointInRect(&mMousePos, &inProgressOrder->mLocOnScreen)) {
						if (mSelectedItemInRecipe->mItemInRecipeType == YOGURT) {
							inProgressOrder->mRecipeItems |= 1 << YOGURTBIT;
						}
						else if (mSelectedItemInRecipe->mItemInRecipeType == STRAWBERRY) {
							inProgressOrder->mRecipeItems |= 1 << STRAWBERRYBIT;
						}
						else if (mSelectedItemInRecipe->mItemInRecipeType == BLUEBERRY) {
							inProgressOrder->mRecipeItems |= 1 << BLUEBERRYBIT;
						}
						inProgressOrder->UpdateSprite();
					}
				}
			}
			delete mAllItemsInRecipe.at(mAllItemsInRecipe.size() - 1);
			mAllItemsInRecipe.pop_back();
			mJustDroppedItemInRecipe = false;
		}
		else if (mJustDroppedOrder) {
			if (SDL_PointInRect(&mMousePos, &mOrderTurnInLocation)) {
				mSelectedOrder->mLocOnScreen = mOrderTurnInLocation;
				mTray.attemptedOrder = mSelectedOrder;
			}
			else {
				mSelectedOrder->mLocOnScreen = mSelectedOrder->mOriginalLocOnScreen;
			}
			mJustDroppedOrder = false;
		}
		else if (mJustDroppedInProgressOrder) {
			if (SDL_PointInRect(&mMousePos, &mTrayLocation)) {
				mTray.attemptedInProgressOrder = mSelectedInProgressOrder;
			}
			mJustDroppedInProgressOrder = false;
		}
		else {
			mSelectedItemInRecipe = NULL;
			mSelectedInProgressOrder = NULL;
			mSelectedOrder = NULL;
		}
	}
}


void StateInGame::Render() {
	SDL_RenderClear(mRenderer);
	SDL_RenderCopy(mRenderer, mTexture, &mBackgroundSpriteRectangle, &mScreenRectangle);
	for (InProgressOrder* inProgressOrder : mAllInProgressOrders) {
		inProgressOrder->Render(mRenderer, mTexture);
	}
	for (ItemInRecipe* food : mAllItemsInRecipe) {
		food->RenderItemInRecipe();
	}
	for (Order* order : mAllOrders) {
		order->RenderOrders(mRenderer, mTexture);
		order->RenderOrderTimer(mRenderer);
	}
	RenderScoreBackground();
	RenderScore();
	RenderTimeLeft();
	SDL_RenderPresent(mRenderer);
}


void StateInGame::NotifyObservers() {
	for (GameStateObserver* observer : mObservers) {
		observer->SetGameState(new StateGameOver(mRenderer, mScore, mHighScore));
	}
}

/// <summary>
/// create all of the food seen in the background image
/// TODO: get locations from file, add loop instead of repetitive code
/// </summary>
void StateInGame::CreateFridgeItemInRecipe() {
	//set location on sprite sheet to strawberries location, then create a strawberries factory
	SDL_Rect locOnSpriteSheet = { 495,435,70,60 };
	mStrawberriesFactory = new StrawberriesFactory(mFlyweightFactory->getItemInRecipeFlyweight(STRAWBERRY, mTexture, locOnSpriteSheet, mRenderer));
	//create a strawberry for each strawberry in the background image
	SDL_Rect locOnScreen = { 5,150,35,30 };
	mAllItemsInRecipe.push_back(mStrawberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 45,150,35,30 };
	mAllItemsInRecipe.push_back(mStrawberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 100,150,35,30 };
	mAllItemsInRecipe.push_back(mStrawberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 145,150,35,30 };
	mAllItemsInRecipe.push_back(mStrawberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 215,150,35,30 };
	mAllItemsInRecipe.push_back(mStrawberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 265,150,35,30 };
	mAllItemsInRecipe.push_back(mStrawberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 325,150,35,30 };
	mAllItemsInRecipe.push_back(mStrawberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 370,150,35,30 };
	mAllItemsInRecipe.push_back(mStrawberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 510,150,35,30 };
	mAllItemsInRecipe.push_back(mStrawberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 375,255,35,30 };
	mAllItemsInRecipe.push_back(mStrawberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 410,255,35,30 };
	mAllItemsInRecipe.push_back(mStrawberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 475,255,35,30 };
	mAllItemsInRecipe.push_back(mStrawberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 520,255,35,30 };
	mAllItemsInRecipe.push_back(mStrawberriesFactory->createItemInRecipe(locOnScreen));

	//change locOnSpriteSheet to be the blueberries location, then create a blueberries factory
	locOnSpriteSheet = { 410,435,75,60 };
	mBlueberriesFactory = new BlueberriesFactory(mFlyweightFactory->getItemInRecipeFlyweight(BLUEBERRY, mTexture, locOnSpriteSheet, mRenderer));
	locOnScreen = { 5,210,35,30 };
	mAllItemsInRecipe.push_back(mBlueberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 160,195,35,30 };
	mAllItemsInRecipe.push_back(mBlueberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 215,195,35,30 };
	mAllItemsInRecipe.push_back(mBlueberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 330,195,35,30 };
	mAllItemsInRecipe.push_back(mBlueberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 390,195,35,30 };
	mAllItemsInRecipe.push_back(mBlueberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 465,195,35,30 };
	mAllItemsInRecipe.push_back(mBlueberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 515,195,35,30 };
	mAllItemsInRecipe.push_back(mBlueberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 95,260,35,30 };
	mAllItemsInRecipe.push_back(mBlueberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 155,260,35,30 };
	mAllItemsInRecipe.push_back(mBlueberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 225,260,35,30 };
	mAllItemsInRecipe.push_back(mBlueberriesFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 270,260,35,30 };
	mAllItemsInRecipe.push_back(mBlueberriesFactory->createItemInRecipe(locOnScreen));

	//change locOnSpriteSheet to be the yogurt location, then create a yogurt factory
	locOnSpriteSheet = { 25,485,55,115 };
	mYogurtFactory = new YogurtFactory(mFlyweightFactory->getItemInRecipeFlyweight(YOGURT, mTexture, locOnSpriteSheet, mRenderer));
	locOnScreen = { 15,90,55,55 };
	mAllItemsInRecipe.push_back(mYogurtFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 105,90,55,55 };
	mAllItemsInRecipe.push_back(mYogurtFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 150,90,55,55 };
	mAllItemsInRecipe.push_back(mYogurtFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 210,90,55,55 };
	mAllItemsInRecipe.push_back(mYogurtFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 260,90,55,55 };
	mAllItemsInRecipe.push_back(mYogurtFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 325,90,55,55 };
	mAllItemsInRecipe.push_back(mYogurtFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 385,90,55,55 };
	mAllItemsInRecipe.push_back(mYogurtFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 455,90,55,55 };
	mAllItemsInRecipe.push_back(mYogurtFactory->createItemInRecipe(locOnScreen));
	locOnScreen = { 505,90,55,55 };
	mAllItemsInRecipe.push_back(mYogurtFactory->createItemInRecipe(locOnScreen));

	locOnSpriteSheet = { 0,420,90,60 };
	mBowlFactory = new BowlFactory(mFlyweightFactory->getItemInRecipeFlyweight(BOWL, mTexture, locOnSpriteSheet, mRenderer));
	locOnScreen = { 585,235,180,65 };
	mAllItemsInRecipe.push_back(mBowlFactory->createItemInRecipe(locOnScreen));
}

void StateInGame::GenerateOrder() {
	//Generate a random number between 2 and 4 inclusive. 2 and 3 are necessary to match
	//items in the ItemInRecipeTypes enum, 4 is the else case for both kinds of fruit
	int num = (rand() % 3) + 2;
	int recipeItems = 0;
	if (num == STRAWBERRY) {
		recipeItems |= 1 << STRAWBERRYBIT;
	}
	else if (num == BLUEBERRY) {
		recipeItems |= 1 << BLUEBERRYBIT;
	}
	else {
		recipeItems |= 1 << STRAWBERRYBIT;
		recipeItems |= 1 << BLUEBERRYBIT;
	}
	mAllOrders.push_back(new Order(mReplacementOrderLocation, recipeItems));
	//add distance between order cards so initial orders are spread out
	//this line won't affect anything after the initial orders because this function will only be called after the replacement order location has been reset
	mReplacementOrderLocation.x += (ORDER_WIDTH + DISTANCE_BETWEEN_ORDER_CARDS);
}

void StateInGame::RenderScore() {
	int digit;
	SDL_Rect locOnScreen;
	for (int i = 0; i < NUM_OF_DIGITS; i++) {
		digit = (mScore / static_cast<int>(pow(10, (NUM_OF_DIGITS - i - 1))) % 10);
		locOnScreen = { 800 - 118 + ((i + 1) * 25),10,NUM_WIDTH, NUM_HEIGHT };
		SDL_RenderCopy(mRenderer, mTexture, &mNumLocsOnSpriteSheet[digit], &locOnScreen);
	}
}

void StateInGame::RenderScoreBackground() {
	SDL_Rect locOnSpriteSheet = { 393,500, 180, 100 };
	SDL_Rect locOnScreen = { 615,5, 180, 100 };
	SDL_RenderCopy(mRenderer, mTexture, &locOnSpriteSheet, &locOnScreen);
}

void StateInGame::RenderTimeLeft() {
	int timeLeft = GAME_TIMER - ((mGameTime - mStartTime) / 1000);
	int minutes = timeLeft / 60;
	int seconds = timeLeft % 60;
	int digit;
	SDL_Rect locOnScreen;
	for (int i = 0; i < NUM_OF_DIGITS; i++) {
		if (i == 0) {
			digit = minutes;
		}
		else {
			digit = (seconds / static_cast<int>(pow(10, (NUM_OF_DIGITS - i - 1))) % 10);
		}
		//800 - 118 + ((i + 1) * 25) is calculating where the digit should be on the screen
		//based on which digit it is
		locOnScreen = { 800 - 118 + ((i + 1) * 25),52,NUM_WIDTH, NUM_HEIGHT };
		SDL_RenderCopy(mRenderer, mTexture, &mNumLocsOnSpriteSheet[digit], &locOnScreen);
	}
}
