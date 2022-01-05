CXX = g++
CXXFLAGS = -g -Wall -MMD
OBJECTS = main.o Block.o Board.o BoardListener.o \
	Level.o Command.o CommandSystem.o \
	MoveCommand.o Rotate.o DropCommand.o \
	LetterCommand.o FileLevel.o \
	SequenceCommand.o QuitCommand.o Restart.o \
	RandomLevel.o LevelManager.o LevelChangeCommand.o \
	RandomControlCommand.o HintCommand.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

${EXEC}:${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean: 
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}

