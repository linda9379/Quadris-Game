#include <iostream>
#include <string>
#include "CommandSystem.h"
#include "MoveCommand.h"
#include "Rotate.h"
#include "Board.h"
#include "DropCommand.h"
#include "LetterCommand.h"
#include "SequenceCommand.h"
#include "QuitCommand.h"
#include "Restart.h"
#include "LevelChangeCommand.h"
#include "RandomControlCommand.h"
#include "HintCommand.h"

int main(int argc, char** argv)
{
    std::string fileName = "sequence.txt";
    int startLevel = 0;

    // handle command line arguments
    for (int i = 0; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-scriptfile") {
            i++;
            if (i < argc) {
                // Check if file exists and set it as the file to read from, if it does not exist then use the default sequence.txt file
                std::ifstream file(argv[i]);
                if (file.is_open()) {
                    fileName = argv[i];
                }
            }
        }
        else if (arg == "-text") {
            // GUI currently unsupported
        }
        else if (arg == "-startlevel") {
            i++;
            if (i < argc) {
                startLevel = std::stoi(argv[i]);
            }
        }
    }

    // correct illegal startlevel values
    if (startLevel < 1) {
        startLevel = 0;
    }
    else if (startLevel > 4) {
        startLevel = 4;
    }

    std::unique_ptr<Board> b = std::make_unique<Board>(fileName, startLevel);
    CommandSystem cmdSys;
    cmdSys.addCommand(std::make_unique<MoveCommand>("left", b.get()));
    cmdSys.addCommand(std::make_unique<MoveCommand>("right", b.get()));
    cmdSys.addCommand(std::make_unique<MoveCommand>("down", b.get()));
    cmdSys.addCommand(std::make_unique<Rotate>("clockwise", b.get()));
    cmdSys.addCommand(std::make_unique<Rotate>("counterclockwise", b.get()));
    cmdSys.addCommand(std::make_unique<DropCommand>(b.get()));
    cmdSys.addCommand(std::make_unique<LetterCommand>("I", b.get()));
    cmdSys.addCommand(std::make_unique<LetterCommand>("J", b.get()));
    cmdSys.addCommand(std::make_unique<LetterCommand>("L", b.get()));
    cmdSys.addCommand(std::make_unique<LetterCommand>("S", b.get()));
    cmdSys.addCommand(std::make_unique<LetterCommand>("T", b.get()));
    cmdSys.addCommand(std::make_unique<LetterCommand>("Z", b.get()));
    cmdSys.addCommand(std::make_unique<LetterCommand>("O", b.get()));
    cmdSys.addCommand(std::make_unique<SequenceCommand>("sequence", b.get(), cmdSys));
    cmdSys.addCommand(std::make_unique<QuitCommand>("quit", b.get()));
    cmdSys.addCommand(std::make_unique<Restart>("restart", b.get()));
    cmdSys.addCommand(std::make_unique<LevelChangeCommand>("levelup", b.get()));
    cmdSys.addCommand(std::make_unique<LevelChangeCommand>("leveldown", b.get()));
    cmdSys.addCommand(std::make_unique<RandomControlCommand>("random", b.get()));
    cmdSys.addCommand(std::make_unique<RandomControlCommand>("norandom", b.get()));
    cmdSys.addCommand(std::make_unique<HintCommand>(b.get()));

    std::cout << *b;
    std::string command;
    std::cout << ">";
    while (getline(std::cin, command)) {

        cmdSys.runCommand(command);

        if (b->getGameOver()) {
            std::cout << "Game Over" << std::endl;
            break;
        }

        std::cout << *b;
        std::cout << ">";
        b->clearHint();
    }


    return 0;
}