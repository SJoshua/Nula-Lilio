#include "basic/Script.h"

Script::Script(void) {
	pos = 0;
}

Script::Script(std::string filename, int pos): pos(pos) {
	readScript(filename);
}

void Script::readScript(std::string filename) {
	tag = filename;
	std::ifstream fs;
	fs.open("./resource/scripts/" + filename);
	std::string tag, str, con, nextBackground, nextCharacter;
	script.push_back({"{INFO}", filename, "", ""});
	while (getline(fs, str)) { 
		if (str.empty()) {
			if (!con.empty()) {
				if (nextCharacter == "-") {
					nextCharacter.clear();
				}
				if (nextBackground == "-") {
					nextBackground = "black";
				}
				script.push_back({tag, con, nextBackground, nextCharacter});
				tag.clear();
				con.clear();
			}
		} else {
			if (str[0] == '#') { // Comments
				continue;
			} else if (str[0] == '@' && str[3] == '[') { // Commands
				auto cmd = str.substr(1, 2);
				if (cmd == "bg") {
					for (unsigned int i = 5; i < str.length(); i++) {
						if (str[i] == ']') {
							nextBackground = str.substr(4, i - 4);
						}
					}
				} else if (cmd == "ch") {
					for (unsigned int i = 5; i < str.length(); i++) {
						if (str[i] == ']') {
							nextCharacter = str.substr(4, i - 4);
						}
					}
				} else if (cmd == "jp") {
					for (unsigned int i = 5; i < str.length(); i++) {
						if (str[i] == ']') {
							tag = "{JUMP}";
							con = str.substr(4, i - 4);
						}
					}
				} else if (cmd == "sl") {
					// to-do
				} else {
					std::cout << "Unsupported command indicator: " << cmd << std::endl;
				}
				
			} else {
				if (tag.empty()) {
					if (str[0] == '[') {
						for (unsigned int i = 0; i < str.length(); i++) {
							if (str[i] == ']') {
								tag = str.substr(1, i - 1);
							}
						}
					}
				}
				for (unsigned int i = 0; i < str.length(); i++) {
					if (str[i] == '\t') {
						if (!con.empty()) {
							con += "\n";
						}
						con += str.substr(i + 1, str.length() - i - 1);
						break;
					} else if (str[i] == '$') {
						tag = "{FLAG}";
						con = str.substr(i, str.length() - i + 2);
					}
				}
			}
		}
	}
	fs.close();
}

std::string Script::getCharacterName(void) {
	return script[pos].name;
}

std::string Script::getText(void) {
	return script[pos].text;
}

std::string Script::getBackground(void) {
	return script[pos].background;
}

std::string Script::getCharacter(void) {
	return script[pos].character;
}

std::string Script::getTag(void) {
	return tag;
}

unsigned int Script::getPosition(void) {
	return pos;
}

void Script::jump(int p) {
	pos = p;
}

bool Script::next(void) {
	pos++;
	if (pos >= script.size()) {
		return false;
	} else {
		if (script[pos].name == "{INFO}" || script[pos].name == "{FLAG}") {
			return next();
		} else if (script[pos].name == "{JUMP}") {
			for (unsigned int i = pos; i < script.size(); i++) {
				if (script[i].name == "{FLAG}" && script[i].text == script[pos].text) {
					pos = i;
					return next();
				}
			}
		}
		return true;
	}
}	