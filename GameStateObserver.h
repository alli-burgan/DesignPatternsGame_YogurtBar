//Observer interface
#pragma once
#include "GameState.h"
class GameState;

class GameStateObserver {
public:
	virtual void SetGameState(GameState* nextGameState) = 0;
};