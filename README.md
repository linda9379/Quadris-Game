Quadris Manual

Working Commands:

- left, right, down: moves the current block in the specified direction
- clockwise, counterclockwise: rotates the current block by 90 degrees
- drop: drops the current block as far down as it will go. Also triggers the next block and 
check for complete rows. Clears complete rows and updates score.
- levelup, leveldown: invokes the levelManager to change the level up or down. 
Levels 0, 1, 2, 3, 4 are supported.
The current block and nextblock belong to the level they were generated at. So if you level up to level 3, 
you will have drop the current and next block before you will see the heaviness take effect.
- random, norandom <file>: relevant during levels 3 and 4. Enables/disables the randomness, instead taking 
input from the file. Will always start reading from the beginning of the file.
- sequence <file>: executes a sequence of commands (eg any of the commands listed above) from the file.
- I, J, L, S, Z, O, T: replaces the current undropped block with a block of the type entered. 
- restart: clears the board, sets level to 0, and starts a new game keeping only the hi-score. If a startlevel was specified from the command line, 
restart will set the level to that level instead of zero.
- hint: gives a hint (the best position the player can currently place the block)
The "best" position is described as the position that can legally be reached that causes the lowest total tower height. 
Also factors in if the "best" position will create overhangs, and trys to avoid them.

- Game will end if the next block cannot be spawned in the top lefthand corner or if a block exceeds the top row of the board

Other supported features:
- prefixes: using a number before a command will cause the command to be executed a number of times equal to the number.
prefixes of 0 and 1 are supported.
- autocomplete-commands: using just the beginning of the command name will cause the correct command to be executed.
eg, ri will be identified as the "right" command.
- smart pointers: No memory leaks, no use of `new` or `delete`

Scoring: 
- When a line is cleared, scoring is calculated by points += (current level + number of lines)^2
- When a block is completely removed, scoring is calculated as score += (lvl block was generated + 1)^2
- Star (*) block in Level 4 does not count towards bonus score

We use a struct called BlockMetaData to store information about when a Block is generated.
Then we use an additional grid to store the "blockID" of every square. When  blockId is fully removed from the 
grid, calculate the bonus points of that block based on the BlockMetaData.

Command Line Options:
- -text: runs the program in text only mode. Currently GUI is unsupported.
- -scriptfile xxx: sets the scriptfile to xxx instead of sequence.txt for level 0
- -startlevel n: starts the game in level n. Default is level 0. If specified, restart command will restart to this level.
- If given invalid command line input, program will start with default settings
- Used <random> Library so a seed was not given





