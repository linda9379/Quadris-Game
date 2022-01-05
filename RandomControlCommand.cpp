#include "RandomControlCommand.h"
#include <cassert>

void RandomControlCommand::run(std::string args)
{
	if (name_ == "random") {
		board_->getLevelManager().disableFile();
	}
	else if (name_ == "norandom") {
		// Checks if theres a file opened and reads and if it does then read the blocks from the given file otherwise, print an error
		std::ifstream file(args);
		if (file.is_open()) {
			board_->getLevelManager().useFromFile(args);
		}
		else {
			std::cout << "ERROR: Invalid input file" << std::endl;
		}
		
	}
	else {
		assert(false);
	}
}

RandomControlCommand::RandomControlCommand(std::string command, Board* board) :Command(command, board)
{
}
