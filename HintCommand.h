#ifndef HINT_COMMAND
#define HINT_COMMAND
#include "Command.h"

class HintCommand :
    public Command
{
    //try dropping a block, returns the "goodness" of the drop as the second parameter
    //of the pair
    std::pair<Block, int> testDrop(Block testBlock);
public:
    virtual void run(std::string args);
    HintCommand(Board* board);
};
#endif
