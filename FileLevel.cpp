#include "FileLevel.h"
#include <fstream>
#include <cassert>
#include <iostream>
// Default constructor
FileLevel::FileLevel()
{
    curIdx_ = -1;
}
// Creates a FileLevel object with the given file 
FileLevel::FileLevel(std::string fileName)
{
    curIdx_ = 0;
    std::ifstream ifs(fileName);
    contents_ = std::string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
}

// Returns the current block
Block FileLevel::current() const
{
    assert(curIdx_ != -1);
    return current_;
}

const std::string VALID_INPUTS = "ijloszt";

// Create the next block
bool FileLevel::advanceNext()
{
    assert(curIdx_ != -1);
    
    //skip inputs until found valid
    for(int i=0;i<contents_.length();i++) {
        if (VALID_INPUTS.find(std::tolower(contents_[curIdx_])) != std::string::npos) {
            current_ = Block::BlockMaker::makeBlock(contents_[curIdx_]);
            curIdx_ = (curIdx_ + 1) % contents_.size();
            return true;
        }
        curIdx_ = (curIdx_ + 1) % contents_.size();
    } 

    std::cerr << "Invalid file. File contains no valid blocks" << std::endl;

    return false;
}
