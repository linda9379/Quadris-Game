#include "LetterCommand.h"
#include <iostream>
#include <assert.h>
// Runs the letter command
void LetterCommand::run(std::string args)
{
	// Creates the new specified block with the corresponding heaviness
	Block::BlockMaker blockmaker;
	Block newBlock;
	bool isHeavy = board_->getCurrentBlock().getHeaviness();

	if (name_ == "I") {
		newBlock = blockmaker.makeBlock('I', isHeavy);
	}
	else if (name_ == "J") {
		newBlock = blockmaker.makeBlock('J', isHeavy);
	}
	else if (name_ == "L") {
		newBlock = blockmaker.makeBlock('L', isHeavy);
	}
	else if (name_ == "S") {
		newBlock = blockmaker.makeBlock('S', isHeavy);
	}
	else if (name_ == "Z") {
		newBlock = blockmaker.makeBlock('Z', isHeavy);
	}
	else if (name_ == "T") {
		newBlock = blockmaker.makeBlock('T', isHeavy);
	}
	else if (name_ == "O") {
		newBlock = blockmaker.makeBlock('O', isHeavy);
	}

	if (board_->checkCollision(newBlock)) {
		//End game if there is a collision
		board_->setGameOver(true);
		return;
	}
	// Set the current block to the new block
	board_->setCurrentBlock(newBlock.setLevel(board_->getLevelManager().getCurrentLevelIndex()));
}

// Letter command constructor
LetterCommand::LetterCommand(std::string name, Board* board) :Command(name, board)
{
	assert(
		name == "I" ||
		name == "J" ||
		name == "L" ||
		name == "S" ||
		name == "Z" ||
		name == "T" ||
		name == "O"
	);
}
