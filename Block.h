#ifndef BLOCK
#define BLOCK
#include <vector>

class Block {
public:
    // empty constructor. Should only be called when no block read yet (default constructor of block)
    Block();
    // Block constructor with all the parameters for each field
    Block(std::vector<std::vector<char>> s, bool h, int x, int y, int levelGeneratedAt);
    // Rotate the block
    Block rotate(bool clockwise) const;
    // Moves the block
    Block move(int dx, int dy) const;
    // Accessors for field values
    std::vector<std::vector<char>> getShape() const;
    bool getHeaviness() const;
    int getX() const;
    int getY() const;
    void setPos(int x, int y);
    Block setLevel(int levelGeneratedAt) const;
    int getLevel() const;

    // BlockMaker class to create blocks of specified chape and heaviness
    class BlockMaker {
    public:
        // Default BlockMaker constructor
        BlockMaker() {};
        // creates a block
        static Block makeBlock(char c, bool heavy = false);
    };

private:
    std::vector<std::vector<char>> shape_;
    bool heavy_;
    int x_;
    int y_;
    int levelGeneratedAt_;
};

#endif
