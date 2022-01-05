#include "QuitCommand.h"

QuitCommand::QuitCommand(std::string name, Board* board) :Command(name, board) {}
// Sets the game to be done
void QuitCommand::run(std::string args)
{
	board_->setGameOver(true);
}

