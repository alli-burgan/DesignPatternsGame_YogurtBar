// Command Pattern Receiver
#pragma once

class Receiver {
public:
    // Receiver class defines the action to be performed.
    virtual void PerformAction(SDL_Rect newLocation) = 0;
};