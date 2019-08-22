#ifndef BASIC_SCRIPT_H
#define BASIC_SCRIPT_H

#include <regex>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <memory>
#include <iostream>

#include "basic/Resource_Manager.h"

struct Position {
	int x, y, tx, ty, speed;
};

struct Unit {
	std::string name, text, background, character;
	Position bgPos, chPos;
	bool select;
	std::vector <std::pair <std::string, std::string>> arguments;
};

class Script {
private:
	unsigned int pos = 0;
	std::vector<Unit> script;
	std::string tag;

public:
	Script(void);

	Script(std::string filename, int pos = 0);

	void readScript(std::string filename);

	std::string getCharacterName(void);

	std::string getText(void);

	std::string getBackground(void);

	std::string getCharacter(void);

	std::string getTag(void);

	std::vector <std::pair <std::string, std::string>> getSelect(void);

	unsigned int getPosition(void);

	void jump(std::string flag);

	bool next(void);
};
#endif
