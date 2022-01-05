#ifndef LETTER_COMMAND
#define LETTER_COMMAND
#include "Command.h"
class LetterCommand : public Command {
public:
    // Run the letter commands and changes the current block to the specified letter
    void run(std::string args);
    // Letter command constructor
    LetterCommand(std::string name, Board* board);

};

#endif
