#include "LevelChangeCommand.h"
#include <cassert>
// Moves the level up or down for the game
void LevelChangeCommand::run(std::string args)
{
	assert(name_ == "levelup" || name_ == "leveldown");

	//true == levelup , false == leveldown
	board_->getLevelManager().levelChange(name_ == "levelup");
	
	std::cout << "Level is now: " << board_->getLevelManager().getCurrentLevelIndex() << std::endl;
	// Reset counter for number of blocks if level 4 is created
	if (board_->getLevelManager().getCurrentLevelIndex() == 4) {
		board_->setBlocksDropped(0);
	}
}

// Level change command constructor
LevelChangeCommand::LevelChangeCommand(std::string name, Board* board) :Command(name, board)
{
}
