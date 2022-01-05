#ifndef QUIT_COMMAND
#define QUIT_COMMAND
#include "Command.h"
#include "CommandSystem.h"
class QuitCommand : public Command {
public:
    void run(std::string args);

    QuitCommand(std::string name, Board* board);
};

#endif
