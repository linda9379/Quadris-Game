#ifndef DROP_COMMAND
#define DROP_COMMAND
#include "Command.h"
class DropCommand : public Command {
public:
    // Runs the drop command and drops the block
    void run(std::string args);
    // Drop Command constructor
    DropCommand(Board* board);

};

#endif
