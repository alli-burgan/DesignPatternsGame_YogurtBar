#pragma once
#include "Command.h"

// Invoker
class Invoker {
public:
    // The setCommand method allows setting the command to
    // be executed.
    void SetCommand(Command* command) { mCommand = command; }

    // The executeCommand method triggers the execution of
    // the command.
    void ExecuteCommand() { mCommand->Execute(); }
private:
    Command* mCommand;
};