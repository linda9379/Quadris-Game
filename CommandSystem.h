#ifndef COMMAND_SYSTEM
#define COMMAND_SYSTEM
#include <vector>
#include <string>
#include <memory>
#include "Board.h"
#include "Command.h"

class CommandSystem {
public:
    // Constructor for creating a command system
    CommandSystem();
    // Runs a command
    void runCommand(std::string command);
    // Adds a command to the command system
    void addCommand(std::unique_ptr<Command> command);

private:
    std::vector<std::unique_ptr<Command>> commands_;

};

#endif
