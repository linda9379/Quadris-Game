#ifndef COMMAND
#define COMMAND
#include <string>
#include <memory>
#include "Board.h"

class Command {
public:
    //args is empty string if the command has no arguments
    virtual void run(std::string args) = 0;
    // Command constructor
    Command(std::string name, Board* board);
    // Gets the name of the command
    std::string getName();

    virtual ~Command() {}
protected:
    std::string name_;
    Board* board_;
};

#endif
