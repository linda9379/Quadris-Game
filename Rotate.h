#ifndef ROTATE
#define ROTATE
#include "Command.h"
class Rotate : public Command {
public:
    // Runs the rotate command
    void run(std::string args);
    // Rotate constructor
    Rotate(std::string name, Board* board);

};

#endif
