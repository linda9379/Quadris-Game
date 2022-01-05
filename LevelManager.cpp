#include "LevelManager.h"
#include <algorithm>

LevelManager::LevelManager() :LevelManager("sequence.txt")
{
}

LevelManager::LevelManager(std::string initialFile)
{
	// Create level 0 
	levels_.push_back(std::make_unique<FileLevel>(initialFile));
	// Create level 1
	levels_.push_back(std::make_unique<RandomLevel, std::unordered_map<char, double>>({
		{'S',1.0 / 12.0},
		{'Z',1.0 / 12.0},
		{'I',1.0 / 6.0},
		{'J',1.0 / 6.0},
		{'L',1.0 / 6.0},
		{'T',1.0 / 6.0},
		{'O',1.0 / 6.0}

		}));
	// Create level 2
	levels_.push_back(std::make_unique<RandomLevel, std::unordered_map<char, double>>({
		{'S',1.0 },
		{'Z',1.0 },
		{'I',1.0 },
		{'J',1.0 },
		{'L',1.0 },
		{'T',1.0 },
		{'O',1.0 }
		}));
	// Create level 3
	std::unique_ptr<RandomLevel> level3 = std::make_unique<RandomLevel, std::unordered_map<char, double>>({
		{'S',2.0 / 9.0 },
		{'Z',2.0 / 9.0 },
		{'I',1.0 / 9.0  },
		{'J',1.0 / 9.0  },
		{'L',1.0 / 9.0  },
		{'T',1.0 / 9.0  },
		{'O',1.0 / 9.0  }
		});
	level3->setHeavy(true);
	levels_.push_back(move(level3));
	// Create level 4
	std::unique_ptr<RandomLevel> level4 = std::make_unique<RandomLevel, std::unordered_map<char, double>>({
	{'S',2.0 / 9.0 },
	{'Z',2.0 / 9.0 },
	{'I',1.0 / 9.0  },
	{'J',1.0 / 9.0  },
	{'L',1.0 / 9.0  },
	{'T',1.0 / 9.0  },
	{'O',1.0 / 9.0  }
		});
	level4->setHeavy(true);
	levels_.push_back(move(level4));
	reset();
}

void LevelManager::reset()
{
	isFileEnabled_ = false;
	currentLevel_ = 0;
}

void LevelManager::levelChange(bool up)
{
	if (up) {
		currentLevel_ = std::min(currentLevel_ + 1, (int)levels_.size() - 1);
	}
	else {
		currentLevel_ = std::max(currentLevel_ - 1, 0);
	}
}

void LevelManager::useFromFile(std::string file)
{
	curFileLevel_ = FileLevel(file);
	isFileEnabled_ = true;
}

void LevelManager::disableFile()
{
	//do nothing if already disabled
	if (!isFileEnabled_) {
		return;
	}

	isFileEnabled_ = false;
	curFileLevel_ = FileLevel(); //clear the current file
}

Level* LevelManager::getCurrentLevel()
{
	if (isFileEnabled_) {
		return &curFileLevel_;
	}
	else {
		return levels_[currentLevel_].get();
	}
}

const Level* LevelManager::getCurrentLevel() const {
	if (isFileEnabled_) {
		return &curFileLevel_;
	}
	else {
		return levels_[currentLevel_].get();
	}
}

int LevelManager::getCurrentLevelIndex() const
{
	return currentLevel_;
}
