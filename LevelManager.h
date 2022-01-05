#ifndef LEVEL_MANAGER
#define LEVEL_MANAGER
#include <string>
#include "FileLevel.h"
#include <memory>
#include "RandomLevel.h"

class LevelManager
{
public:
	//defaults to using "sequence.txt" as initial file
	LevelManager();
	LevelManager(std::string initialFile);

	void reset();
	void levelChange(bool up);

	void useFromFile(std::string file);
	void disableFile();

	Level* getCurrentLevel();
	const Level* getCurrentLevel() const;
	int getCurrentLevelIndex() const;
private:
	//note that isFileEnabled is independent of level
	//this means a separate file can be loaded to override
	//the blocks from any level
	bool isFileEnabled_;
	FileLevel curFileLevel_;
	std::vector<std::unique_ptr<Level>> levels_;
	int currentLevel_;
};
#endif