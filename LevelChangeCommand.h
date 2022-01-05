#ifndef LEVEL_CHANGE_COMMAND
#define LEVEL_CHANGE_COMMAND
#include "Command.h"
class LevelChangeCommand :
    public Command
{
public:
    // Changes the level
    void run(std::string args);
    // Level change constructor
    LevelChangeCommand(std::string name, Board* board);
};
#endif