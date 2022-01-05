#include "Command.h"
// Command constructor
Command::Command(std::string name, Board* board) :name_{ name }, board_ {board}
{
}

// Returns the name of the command
std::string Command::getName()
{
	return name_;
}
