#include <cassert>
#include <unordered_set>
#include "Board.h"
#include "FileLevel.h"
#include "RandomLevel.h"

// Default board constructor
Board::Board(std::string fileName, int startLevel) : fileName_(fileName), startLevel_{ startLevel }
{
	rows_ = 18;
	columns_ = 11;
	highScore_ = 0;

	reset(); //reuse the code in reset() initialize all other variables
}

// Adds aboard listener
void Board::addListener(BoardListener blistener) {

}

bool Board::checkCollision(Block b) {
	std::vector<std::vector<char>> blockShape = b.getShape();
	int blockWidth = blockShape[0].size();
	int blockHeight = blockShape.size();
	int boardWidth = columns_;
	int boardHeight = rows_;

	//Check all non-empty cells for collisions
	for (int blockX = 0; blockX < blockWidth; blockX++) {
		for (int blockY = 0; blockY < blockHeight; blockY++) {

			int boardX = b.getX() + blockX;
			int boardY = b.getY() + blockY;

			if (blockShape[blockY][blockX] != ' ') {
				//check out of bounds
				if (boardX < 0 || boardY < 0 || boardX >= boardWidth || boardY >= boardHeight) {
					return true;
				}

				//check collision with other grid
				if (grid_[boardY][boardX] != ' ') {
					return true;
				}
			}
		}
	}

	return false;


}

// Sets the current block
void Board::setCurrentBlock(Block b) {
	currentBlock_ = b;
}

// Gets the current block
const Block& Board::getCurrentBlock() const
{
	return currentBlock_;
}

// Add the current block to the board
void Board::confirmCurrentBlock() {
	// If level is 4 increment number of blocks dropped
	if (lvlManager_.getCurrentLevelIndex() == 4) {
		++blocksDropped_;
	}
	// Incrememt the block ID and change the blockmetadata 
	currentBlockID_++;
	BlockMetadata curBlockMetadata;
	curBlockMetadata.levelGeneratedAt = currentBlock_.getLevel();
	curBlockMetadata.remainingToClear = 0;

	std::vector<std::vector<char>> blockShape = currentBlock_.getShape();
	int blockWidth = blockShape[0].size();
	int blockHeight = blockShape.size();

	//copy all blocks of currentBlock into the grid
	for (int blockX = 0; blockX < blockWidth; blockX++) {
		for (int blockY = 0; blockY < blockHeight; blockY++) {

			int boardX = currentBlock_.getX() + blockX;
			int boardY = currentBlock_.getY() + blockY;

			if (blockShape[blockY][blockX] != ' ') {
				grid_[boardY][boardX] = blockShape[blockY][blockX];
				blockID_[boardY][boardX] = currentBlockID_;
				curBlockMetadata.remainingToClear++;
			}
		}
	}

	blockInfo_[currentBlockID_] = curBlockMetadata;

	//test if the next block causes a collision
	//if it does the game is ended
	Block tmp = nextBlock_;
	if (checkCollision(tmp)) {
		gameOver_ = true;
	}
	else {
		setCurrentBlock(nextBlock_);

		Level* curLevel = lvlManager_.getCurrentLevel();

		if (!curLevel->advanceNext()) {
			//TODO
			std::cout << "You won!" << std::endl;
			return;
		}
		nextBlock_ = curLevel->current().setLevel(lvlManager_.getCurrentLevelIndex());
	}
}

void Board::clearCompletedRows() {
	// Check from the bottom to the top rows to see which are complete
	int numClearedRows = 0;
	for (int i = 3; i < rows_; ++i) {
		// Check if every column in a row contains a letter, if it does not then move on
		bool rowComplete = true;
		for (int j = 0; j < columns_; ++j) {
			// Check if there is a blank block, if there is then set rowComplete to false and break out of the loop
			if (grid_[i][j] == ' ') {
				rowComplete = false;
				break;
			}
		}
		// If there is a complete row, delete it and add a new empty row into the grid
		if (rowComplete) {
			++numClearedRows;

			//update the remainingToClear number for each block which got partially removed
			for (int k = 0; k < columns_; ++k) {
				if (grid_[i][k] != '*') {
					BlockMetadata& metadata = blockInfo_[blockID_[i][k]];
					metadata.remainingToClear--;

					//if there are 0 remaining to clear, the block has completely been cleared
					//and bonus must be updated.
					assert(metadata.remainingToClear >= 0);
					if (metadata.remainingToClear == 0) {
						updateBonus(metadata);
						blockInfo_.erase(blockID_[i][k]);
					}
				}
			}

			// clear then add a new empty row to the top of the board
			grid_.erase(grid_.begin() + i);
			grid_.insert(grid_.begin(), std::vector<char>(columns_, ' '));

			// update the grid of block IDs as well
			blockID_.erase(blockID_.begin() + i);
			blockID_.insert(blockID_.begin(), std::vector<int>(columns_, 0));
		}
	}
	// Calculate the score for the number of cleared rows
	if (numClearedRows > 0) {
		calculateScore(numClearedRows);
	}

	// Recheck for if the current block can be generated
	if (numClearedRows > 0 && gameOver_) {
		Block tmp = nextBlock_;
		if (!checkCollision(tmp)) {
			gameOver_ = false;
			setCurrentBlock(nextBlock_);
			nextBlock_ = lvlManager_.getCurrentLevel()->current().setLevel(lvlManager_.getCurrentLevelIndex());
		}

	}
}

// Calculates the score
void Board::calculateScore(int numOfClearedRows) {
	int currentLevel = lvlManager_.getCurrentLevelIndex();
	score_ += (currentLevel + numOfClearedRows) * (currentLevel + numOfClearedRows);
	if (score_ > highScore_) {
		highScore_ = score_;
	}
}

// Calculates bonus score
void Board::updateBonus(BlockMetadata& clearedBlock)
{
	score_ += (clearedBlock.levelGeneratedAt + 1) * (clearedBlock.levelGeneratedAt + 1);
}

// Resets the board to an empty board and set the level back to 0
void Board::reset() {
	// Reset everything but the high score
	score_ = 0;
	currentBlockID_ = 0;
	gameOver_ = false;
	blocksDropped_ = 0;
	ishintShown_ = false;

	//sets the block to the initial one given by LevelManager
	lvlManager_ = LevelManager(fileName_);
	//set the starting level
	for (int i = 0; i < startLevel_; i++) {
		lvlManager_.levelChange(true); // level up
	}

	Level* level = lvlManager_.getCurrentLevel();
	level->advanceNext();
	currentBlock_ = level->current().setLevel(lvlManager_.getCurrentLevelIndex());
	level->advanceNext();
	nextBlock_ = level->current().setLevel(lvlManager_.getCurrentLevelIndex());


	// Creates a 2D vector for the grid of 18x11 
	blockID_ = std::vector<std::vector<int>>(rows_, std::vector<int>(columns_, 0));
	grid_ = std::vector<std::vector<char>>(rows_, std::vector<char>(columns_, ' '));
}

void Board::checkTopThreeRows() {
	// Check to see if any block in the top three rows if there is then end the game
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < columns_; ++j) {
			if (grid_[i][j] != ' ') {
				gameOver_ = true;
			}
		}
	}
}

// Get if game over
bool Board::getGameOver() {
	return gameOver_;
}

// Set game over field
bool Board::setGameOver(bool isOver) {
	gameOver_ = isOver;
}

// Return the level manager for the board
LevelManager& Board::getLevelManager()
{
	return lvlManager_;
}

// Gets the current block ID(number of blocks dropped)
int Board::getCurrentBlockID() {
	return currentBlockID_;
}

// Return the number of blocks dropped
int Board::getBlocksDropped() {
	return blocksDropped_;
}

// Sets the number of blocks dropped
void Board::setBlocksDropped(int dropped) {
	blocksDropped_ = dropped;
}

// Adds a star block to the middle of the board
void Board::addStarBlock() {
	// Increment the row counter until the lowest possible block on the board is found or the edge of the board is reached
	int i = 2;
	while (grid_[i + 1][5] == ' ') {
		++i;
		if (i == 17) {
			break;
		}
	}
	// set the empty square to a star block
	grid_[i][5] = '*';
}

void Board::setHint(Block hint)
{
	hint_ = hint;
	ishintShown_ = true;
}

void Board::clearHint()
{
	ishintShown_ = false;
}

int Board::getWidth() const
{
	return columns_;
}

int Board::getHeight() const
{
	return rows_;
}

char Board::getGridCellAt(int row, int col) const
{
	return grid_[row][col];
}

std::ostream& operator<<(std::ostream& sout, const Board& b) {
	std::vector<std::vector<char>> curBlockShape = b.currentBlock_.getShape();
	int currBlockWidth = curBlockShape[0].size();
	int currBlockHeight = curBlockShape.size();
	// Prints the level and score information
	sout << "   Level: " << b.lvlManager_.getCurrentLevelIndex() << std::endl;
	sout << "   Score: " << b.score_ << std::endl;
	sout << "   Hi-Score: " << b.highScore_ << std::endl;

	sout << "   ";
	for (int i = 0; i < b.columns_; i++) {
		sout << "-";
	}
	sout << std::endl;
	// Print the characters in board
	for (int i = 0; i < b.rows_; ++i) {
		if (i + 1 < 10) {
			sout << i + 1 << "  ";
		}
		else {
			sout << i + 1 << " ";
		}


		for (int j = 0; j < b.columns_; ++j) {
			//print a separate character if the current block covers it
			int blockX = j - b.currentBlock_.getX();
			int blockY = i - b.currentBlock_.getY();

			bool isNotWithinBlock = blockX < 0 || blockY < 0 || blockX >= currBlockWidth || blockY >= currBlockHeight;

			if (b.ishintShown_) {
				std::vector<std::vector<char>> hintShape = b.hint_.getShape();
				int hintBlockWidth = hintShape[0].size();
				int hintBlockHeight = hintShape.size();
				int hintX = j - b.hint_.getX();
				int hintY = i - b.hint_.getY();
				bool isNotWithinHint = hintX < 0 || hintY < 0 || hintX >= hintBlockWidth || hintY >= hintBlockHeight;
				if (!isNotWithinHint) {

					if (hintShape[hintY][hintX] != ' ') {
						assert(b.grid_[i][j] == ' ');
						sout << '?';
						continue;
					}
				}
			}

			if (!isNotWithinBlock) {
				if (curBlockShape[blockY][blockX] != ' ') {
					assert(b.grid_[i][j] == ' ');
					sout << curBlockShape[blockY][blockX];
					continue;
				}
			}

			sout << b.grid_[i][j];


		}
		sout << "  " << std::endl;
	}
	sout << "   ";
	for (int i = 0; i < b.columns_; i++) {
		sout << "-";
	}
	sout << std::endl;

	// Print the next block going into the board
	sout << "   Next:" << std::endl;
	std::vector<std::vector<char>> nextShape = b.nextBlock_.getShape();
	for (int i = 0; i < nextShape.size(); ++i) {
		sout << "     ";
		for (int j = 0; j < nextShape[i].size(); ++j) {
			sout << nextShape[i][j];
		}
		sout << std::endl;
	}

	return sout;
}