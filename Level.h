#include "Block.h"
#ifndef LEVEL
#define LEVEL

class Level {
public:
    // returns the next block but doesn't mutate 
    virtual Block current() const = 0;

    // advances to the next block
    // THIS IS CALLED BEFORE THE FIRST CALL TO peekNext()
    // returns false if there is no next block
    virtual bool advanceNext() = 0;
    virtual ~Level() {}
private:
};

#endif