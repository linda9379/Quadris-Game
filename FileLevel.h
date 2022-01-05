#ifndef FILE_LEVEL
#define FILE_LEVEL
#include "Level.h"
#include <string>
#include <fstream>
class FileLevel :
    public Level
{
public:
    //default constructor if object is not intialized yet
    FileLevel();
    FileLevel(std::string fileName);
    // Returns the current block
    virtual Block current() const;
    // Gets the next block
    virtual bool advanceNext();
private:
    Block current_;
    std::string contents_;
    int curIdx_;
};
#endif
