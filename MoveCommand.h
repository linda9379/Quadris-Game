#ifndef MOVE_COMMAND
#define MOVE_COMMAND
#include "Command.h"
class MoveCommand : public Command {
public:
    void run(std::string args);

    MoveCommand(std::string name, Board* board);

};

#endif
