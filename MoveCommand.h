// Concrete Command
#pragma once
#include "Command.h"
#include "ItemInRecipe.h"

class MoveCommand : public Command {
public:
    // ConcreteCommand takes a reference to a Receiver
    // object in its constructor.
    MoveCommand(ItemInRecipe* foodReceiver, SDL_Rect newLocation) : mItemInRecipeReceiver(foodReceiver), mNewPosition(newLocation) {}

    // The execute method calls the action on the Receiver.
    virtual void Execute() override { 
        mItemInRecipeReceiver->PerformAction(mNewPosition); 
    }

private:
    ItemInRecipe* mItemInRecipeReceiver;
    SDL_Rect mNewPosition;
};