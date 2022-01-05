#ifndef BOARD
#define BOARD
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>
#include "Block.h"
#include "Level.h"
#include "BoardListener.h"
#include "LevelManager.h"

//stores additional data required for calculating scores and bonuses
struct BlockMetadata {
    int remainingToClear;
    int levelGeneratedAt;
};

class Board {

public:
    // Default Board constructor
    Board(std::string FileName, int startLevel = 0);
    // Adds a board listener
    void addListener(BoardListener);
    // Checks for collisions on the board with the current block
    bool checkCollision(Block);
    // Sets the current block
    void setCurrentBlock(Block);
    // Gets the current block
    const Block& getCurrentBlock() const;
    // Puts the current block on the board
    void confirmCurrentBlock();
    // Clears the completely filled rows
    void clearCompletedRows();
    // Calculates the score
    void calculateScore(int numOfClearedRows);
    // Calculates bonus score
    void updateBonus(BlockMetadata& clearedBlock);
    // Resets the board
    void reset();
    // Checks the top three rows to ensure no blocks are there
    void checkTopThreeRows();
    // Gets whether or not the game is over
    bool getGameOver();
    // Sets the game over field
    bool setGameOver(bool isOver);
    // Gets the Level Manager that manages levels
    LevelManager& getLevelManager();
    // Gets the current block ID
    int getCurrentBlockID();
    // Returns the number of blocks dropped
    int getBlocksDropped();
    // Sets the number of blocks dropped
    void setBlocksDropped(int dropped);
    // Adds a star block to the middle of the board
    void addStarBlock();
    // Overload output operator to print the board
    friend std::ostream& operator<<(std::ostream& sout, const Board& b);

    // Sets the current hint
    void setHint(Block hint);
    void clearHint();

    int getWidth() const;
    int getHeight() const;
    char getGridCellAt(int row, int col) const;
private:
    Block currentBlock_;
    Block nextBlock_;
    std::vector<std::vector<char>> grid_;
    std::vector<std::vector<int>> blockID_; //stores the corresponding block ID of each cell so we can look up info for scoring
    int currentBlockID_; // stores the current block ID
    std::unordered_map<int, BlockMetadata> blockInfo_;
    int rows_;
    int columns_;
    int score_;
    int highScore_;
    int blocksDropped_;
    LevelManager lvlManager_;
    bool gameOver_;
    std::string fileName_;

    Block hint_;
    bool ishintShown_;
    int startLevel_;
};

#endif