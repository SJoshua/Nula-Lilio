#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>
#include "Resource_Manager.h"
#include "Texture.h"

class Script {
private:
	std::string text, name, background, character;
public:
	Script(std::string filename) {
		text = "これは脚本ですよーっと。\n頑張ってね！";
		name = "Rin";
		background = "background.jpg";
		character = "character.png";
	}

	std::string getCharacterName(void) {
		return name;
	}

	std::string getText(void) {
		return text;
	}

	std::string getBackground(void) {
		return background;
	}

	std::string getCharacter(void) {
		return character;
	}	
};
#endif