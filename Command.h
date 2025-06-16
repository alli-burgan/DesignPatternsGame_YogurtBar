#pragma once
// Command interface
class Command {
public:
    // The execute method is declared in the Command
    // interface.
    virtual void Execute() = 0;
};