#include "DropCommand.h"

void DropCommand::run(std::string args)
{
	Block curBlock = board_->getCurrentBlock();

	//keep moving the block down until it hits something
	while (!board_->checkCollision(curBlock.move(0, 1))) {
		curBlock = curBlock.move(0, 1);
	}
	// Sets the current block as the moved block 
	board_->setCurrentBlock(curBlock);
	board_->confirmCurrentBlock();
	// If the level is 4 then add a one grid block to the middle of the board
	if (board_->getLevelManager().getCurrentLevelIndex() == 4) {
		// Add block to board every for five blocks dropped
		if (board_->getBlocksDropped() % 5 == 0) {
			board_->addStarBlock();
		}
	}
	// Check if any row can be cleared 
	board_->clearCompletedRows();
	// Check if any blocks are out of the board range
	board_->checkTopThreeRows();
}

// Drop command default constructor
DropCommand::DropCommand(Board* board) :Command("drop", board)
{
}
