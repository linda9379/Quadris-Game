#include "HintCommand.h"

std::pair<Block, int> HintCommand::testDrop(Block testBlock)
{
	//keep moving the block down until it hits something
	Block droppedBlock = testBlock;
	while (!board_->checkCollision(droppedBlock.move(0, 1))) {
		droppedBlock = droppedBlock.move(0, 1);
	}

	const std::vector<std::vector<char>>& shape = droppedBlock.getShape();
	int height = droppedBlock.getShape().size();
	int width = droppedBlock.getShape()[0].size();

	int goodness = 0;

	//check if this drop causes overhangs?
	int tallestCell = 0;
	for (int col = 0;col < width; col++) {

		//search for tallest cell to use below
		for (int row = 0;row < height;row++) {
			if (shape[row][col] != ' ') {
				tallestCell = std::min(tallestCell, row);
			}
		}

		//find the lowest cell this block covers in the current column
		for (int row = height - 1;row >= 0;row--) {
			if (shape[row][col] != ' ') {
				
				//the more open cells this block covers, the worse it is
				for (int y = row + droppedBlock.getY() + 1;y < board_->getHeight();y++) {
					if (board_->getGridCellAt(y, col + droppedBlock.getX()) == ' ') {
						goodness -= 10;
					}
				}

				break;
			}
		}
	}

	//the closer the tallest cell in the block is to the ground, the better it is?
	goodness += droppedBlock.getY() + tallestCell;

	return { droppedBlock, goodness };
}

void HintCommand::run(std::string args)
{
	//try all combinations of rotation and position and try to drop
	Block testHint = board_->getCurrentBlock();
	Block bestHint = testHint;
	int bestGoodness = std::numeric_limits<int>::min();
	for (int rot = 0;rot < 4;rot++) {

		//try moving the block left and right and drop it
		for (Block moved = testHint;!board_->checkCollision(moved);moved = moved.move(-1, 0)) {
			std::pair<Block,int> dropped = testDrop(moved);
			if (dropped.second>bestGoodness) {
				bestHint = dropped.first;
				bestGoodness = dropped.second;
			}
		}
		for (Block moved = testHint;!board_->checkCollision(moved);moved = moved.move(1, 0)) {
			std::pair<Block, int> dropped = testDrop(moved);
			if (dropped.second > bestGoodness) {
				bestHint = dropped.first;
				bestGoodness = dropped.second;
			}
		}

		testHint = testHint.rotate(true);
		
	}
	board_->setHint(bestHint);
		
}

HintCommand::HintCommand(Board* board):Command("hint", board)
{
}
