#ifndef RESTART
#define RESTART
#include "Command.h"
#include "CommandSystem.h"
class Restart : public Command {
public:
    // Constructor
    Restart(std::string name, Board* board);
    // Runs the command
    void run(std::string args);
};

#endif
