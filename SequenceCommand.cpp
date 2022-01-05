#include "SequenceCommand.h"
#include <iostream>
#include <fstream>

void SequenceCommand::run(std::string args)
{
	std::ifstream file(args);
	// Checks if theres a file opened and reads and executes all the command in the file
	if (file.is_open()) {
		std::string command;

		while (getline(file, command)) {

			cmdSys_.runCommand(command);

			if (board_->getGameOver()) {
				return;
			}

			std::cout << *board_;
		}
	}
	else {
		// If file not found then print error
		std::cout << "ERROR: Invalid input file" << std::endl;
	}
}

SequenceCommand::SequenceCommand(std::string name, Board* board, CommandSystem& cmdSys) :Command(name, board), cmdSys_{ cmdSys } {}