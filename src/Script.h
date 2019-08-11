#ifndef SCRIPT_H
#define SCRIPT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Resource_Manager.h"
#include "Texture.h"

struct page {
	std::string name, text, background, character;	
};

class Script {
private:
    int pos;
	std::vector <page> script;
public:
	Script(void) {}
	Script(std::string filename, int pos = 0): pos(pos) {
        std::fstream fs("./resource/scripts/" + filename, fs.in);
		std::string tag, str, con, nextBackground, nextCharacter;
		script.push_back({"<INFO>", filename, "", ""});
		while (getline(fs, str)) { 
			if (str.empty()) {
				if (!con.empty()) {
					script.push_back({tag, con, nextBackground, nextCharacter});
					tag.clear();
					con.clear();
				}
			} else {
				if (str[0] == '#') { // Comments
					continue;
				} else if (str[0] == '@') { // Commands
					if (str.substr(1, 3) == "bg[") {
						for (int i = 5; i < str.length(); i++) {
							if (str[i] == ']') {
								nextBackground = str.substr(4, i - 4);
							}
						}
					}
					if (str.substr(1, 3) == "ch[") {
						for (int i = 5; i < str.length(); i++) {
							if (str[i] == ']') {
								nextCharacter = str.substr(4, i - 4);
							}
						}
					}
				} else {
					if (tag.empty()) {
						if (str[0] == '[') {
							for (int i = 0; i < str.length(); i++) {
								if (str[i] == ']') {
									tag = str.substr(1, i - 1);
								}
							}
						}
					}
					for (int i = 0; i < str.length(); i++) {
						if (str[i] == '\t') {
							if (!con.empty()) {
								con += "\n";
							}
							con += str.substr(i + 1, str.length() - i - 1);
							break;
						}
					}
				}
			}
		}
		fs.close();
	}

	std::string getCharacterName(void) {
		return script[pos].name;
	}

	std::string getText(void) {
		return script[pos].text;
	}

	std::string getBackground(void) {
		return script[pos].background;
	}

	std::string getCharacter(void) {
		return script[pos].character;
	}

    void next(void) {
		pos++;
    }	
};
#endif
