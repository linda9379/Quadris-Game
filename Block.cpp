#include "Block.h"
#include <cctype>
#include <iostream>

// Empty constructor. Should only be called when no block read yet (default constructor of block)
Block::Block() {

}

// Block constructor with parameters for all the field values
Block::Block(std::vector<std::vector<char>> s, bool h = false, int x = 0, int y = 3, int levelGeneratedAt = 0) : 
	shape_{ s }, heavy_{ h }, x_{ x }, y_{ y }, levelGeneratedAt_{ levelGeneratedAt }{

}

// Rotates the block
Block Block::rotate(bool clockwise) const {
	std::vector<std::vector<char>> newShape;
	if (clockwise) {
		// Flip the row and the columns and rotate the block clockwise
		for (int i = 0; i < shape_[0].size(); ++i) {
			std::vector<char> row;
			for (int j = 0; j < shape_.size(); ++j) {
				row.push_back(shape_[shape_.size() - 1 - j][i]);
			}
			newShape.push_back(row);
		}
	}
	else {
		// Flip the row and the columns and rotate the block counterclcokwise
		for (int i = 0; i < shape_[0].size(); ++i) {
			std::vector<char> row;
			for (int j = 0; j < shape_.size(); ++j) {
				row.push_back(shape_[j][shape_[0].size() - 1 - i]);
			}
			newShape.push_back(row);
		}
	}
	int yValue = shape_.size() - shape_[0].size();
	// Return a new block with the new rotation
	return Block(newShape, heavy_, x_, y_ + yValue, levelGeneratedAt_);
}

// Moves the block down, right, or left
Block Block::move(int dx, int dy) const
{
	// Returns a new moved block
	return Block(shape_, heavy_, x_ + dx, y_ + dy, levelGeneratedAt_);
}

// Creates a block with the specified shape and heaviness
Block Block::BlockMaker::makeBlock(char c, bool heavy) {
	c = tolower(c);
	std::vector<std::vector<char>> shape;
	std::vector<char> row1;
	std::vector<char> row2;
	switch (c) {
	case 'i':
		row1.push_back('I');
		row1.push_back('I');
		row1.push_back('I');
		row1.push_back('I');
		shape.push_back(row1);
		break;
	case 'j':
		row1.push_back('J');
		row1.push_back(' ');
		row1.push_back(' ');
		row2.push_back('J');
		row2.push_back('J');
		row2.push_back('J');
		shape.push_back(row1);
		shape.push_back(row2);
		break;
	case 'l':
		row1.push_back(' ');
		row1.push_back(' ');
		row1.push_back('L');
		row2.push_back('L');
		row2.push_back('L');
		row2.push_back('L');
		shape.push_back(row1);
		shape.push_back(row2);
		break;
	case 'o':
		row1.push_back('O');
		row1.push_back('O');
		row2.push_back('O');
		row2.push_back('O');
		shape.push_back(row1);
		shape.push_back(row2);
		break;
	case 's':
		row1.push_back(' ');
		row1.push_back('S');
		row1.push_back('S');
		row2.push_back('S');
		row2.push_back('S');
		row2.push_back(' ');
		shape.push_back(row1);
		shape.push_back(row2);
		break;
	case 'z':
		row1.push_back('Z');
		row1.push_back('Z');
		row1.push_back(' ');
		row2.push_back(' ');
		row2.push_back('Z');
		row2.push_back('Z');
		shape.push_back(row1);
		shape.push_back(row2);
		break;
	case 't':
		row1.push_back('T');
		row1.push_back('T');
		row1.push_back('T');
		row2.push_back(' ');
		row2.push_back('T');
		row2.push_back(' ');
		shape.push_back(row1);
		shape.push_back(row2);
		break;
	default:
		// Throw error if illegal block character is given
		std::cerr << "ERROR, illegal block type character " << c << std::endl;
		return Block(shape);
	}
	// Return the newly created block
	return Block(shape, heavy);
}

// Gets the shape of the block
std::vector<std::vector<char>> Block::getShape() const {
	return shape_;
}

// Gets the heaviness of the block
bool Block::getHeaviness() const {
	return heavy_;
}

// Gets the x coordinate of the block
int Block::getX() const
{
	return x_;
}

// Get the y coordinate of the block
int Block::getY() const
{
	return y_;
}

void Block::setPos(int x, int y)
{
	x_ = x;
	y_ = y;
}

Block Block::setLevel(int levelGeneratedAt) const
{
	return Block(shape_, heavy_, x_, y_, levelGeneratedAt);
}

int Block::getLevel() const
{
	return levelGeneratedAt_;
}
