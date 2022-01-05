#include "Rotate.h"
#include <iostream>
#include <assert.h>

void Rotate::run(std::string args)
{
	Block currBlock = board_->getCurrentBlock();
	// Set a temporary block as the current block and rotate it to the corresponding command
	Block tmpBlock;
	if (name_ == "clockwise") {
		tmpBlock = currBlock.rotate(true);
	}
	else if (name_ == "counterclockwise") {
		tmpBlock = currBlock.rotate(false);
	}

	// Check if the temporary moved block will have a collision
	bool hasCollision = board_->checkCollision(tmpBlock);
	if (hasCollision) {
		std::cout << "invalid move" << std::endl;
	}
	else {
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

Rotate::Rotate(std::string name, Board* board) :Command(name, board)
{
	assert(
		name == "clockwise" ||
		name == "counterclockwise"
	);
}
