#ifndef SCRIPT_H
#define SCRIPT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

#include "basic/Resource_Manager.h"

struct page {
	std::string name, text, background, character;
};

class Script {
private:
	int pos = 0;
	std::vector <page> script;
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

	void jump(int p);

	bool next(void);
};
#endif
