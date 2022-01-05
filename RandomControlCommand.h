#ifndef RANDOM_CONTROL_COMMAND
#define RANDOM_CONTROL_COMMAND
#include "Command.h"

//random/norandom
class RandomControlCommand :
    public Command
{
public:
    void run(std::string args);

    RandomControlCommand(std::string command, Board* board);
};
#endif