#ifndef SEQUENCE_COMMAND
#define SEQUENCE_COMMAND
#include "Command.h"
#include "CommandSystem.h"
class SequenceCommand : public Command {
public:
    // Runs the sequence command
    void run(std::string args);
    // Sequence command constructor
    SequenceCommand(std::string name, Board* board, CommandSystem& cmdSys);

private:
    CommandSystem& cmdSys_;
};

#endif
