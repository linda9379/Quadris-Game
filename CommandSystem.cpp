#include "CommandSystem.h"
#include <iostream>

CommandSystem::CommandSystem() {
}

void CommandSystem::runCommand(std::string command)
{
	//scan for the longest numeric prefix of command
	int idx = 0;
	while (idx < command.size() && command[idx] >= '0' && command[idx] <= '9') {
		idx++;
	}

	//parse multiplier from this number
	int multiplier = 1;
	if (idx > 0) {
		multiplier = std::stoi(command.substr(0, idx));
		command = command.substr(idx);
	}


	//split command by space to check for extra args
	std::size_t space = command.find(' ');
	std::string commandName = command.substr(0, space);
	std::string args = "";
	if (space != std::string::npos) {
		args = command.substr(space + 1);
	}

	//search for commands matching, and call run
	int match = -1;
	for (int i = 0; i < (int)commands_.size(); i++) {
		const std::string& checkAgainst = commands_[i]->getName();

		//check if prefix matches
		if (checkAgainst.size() >= commandName.size() 
			&& checkAgainst.substr(0,commandName.size()) == commandName) {
			if (match != -1) {
				//multiple commands match
				std::cout << "ERROR: multiple commands match" << std::endl;
				return;
			}
			else {
				match = i;
			}
		}
	}

	if (match == -1) {
		std::cout << "ERROR: no such command " << commandName << " found" << std::endl;

	}
	else {
		for (int i = 0;i < multiplier;i++) {
			commands_[match]->run(args);
		}
	}
}

void CommandSystem::addCommand(std::unique_ptr<Command> command)
{
	commands_.push_back(move(command));
}
