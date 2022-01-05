#include "Restart.h"
// Restart Constructor
Restart::Restart(std::string name, Board* board) :Command(name, board) {
}
// Resets the board to restart the game
void Restart::run(std::string args)
{
	board_->reset();
}