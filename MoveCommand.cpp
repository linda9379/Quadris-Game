#include "MoveCommand.h"
#include <iostream>
#include <assert.h>

void MoveCommand::run(std::string args)
{
	Block currBlock = board_->getCurrentBlock();

	// Set a temporary block as the current block and move it to the corresponding command
	Block tmpBlock;
	if (name_ == "left") {
		tmpBlock = currBlock.move(-1, 0);
	}
	else if (name_ == "right") {
		tmpBlock = currBlock.move(1, 0);
	}
	else if (name_ == "down") {
		tmpBlock = currBlock.move(0, 1);
	}

	// Check if the temporary moved block will have a collision
	bool hasCollision = board_->checkCollision(tmpBlock);
	if (hasCollision) {
		std::cout << "invalid move" << std::endl;
	}
	else {
		//no collision, we can move the block
		currBlock = tmpBlock;
	}

	// Check if the block is heavy to move the block down by one row after any move command
	if (currBlock.getHeaviness()) {
		tmpBlock = currBlock.move(0, 1);
		if (!board_->checkCollision(tmpBlock)) {
			currBlock = tmpBlock;
		}
	}

	board_->setCurrentBlock(currBlock);

}

MoveCommand::MoveCommand(std::string name, Board* board) :Command(name, board)
{
	assert(
		name == "left" ||
		name == "down" ||
		name == "right"
	);
}

