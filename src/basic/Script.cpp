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
	std::vector<std::pair<std::string, std::string>> select;
	script.push_back({ "{INFO}", filename, "", "" });
	while (getline(fs, str)) {
		if (str.empty()) {
			if (!con.empty()) {
				if (nextCharacter == "-") {
					nextCharacter.clear();
				}
				if (nextBackground == "-") {
					nextBackground = "black";
				}
				Unit nxt = { tag, con, nextBackground, nextCharacter };
				if (!select.empty()) {
					nxt.select = true;
					nxt.arguments = select;
					select.clear();
				}
				script.push_back(nxt);
				tag.clear();
				con.clear();
			}
		} else {
			if (str[0] == '#') {  // Comments
				continue;
			} else if (str[0] == '@' && str[3] == '[') {  // Commands
				auto cmd = str.substr(1, 2);
				unsigned last = 4;
				for (; last < str.length(); last++) {
					if (str[last] == ']') {
						break;
					}
				}
				auto para = str.substr(4, last - 4);
				std::string ext;
				int left = 0, right = 0;
				for (; last < str.length(); last++) {
					if (str[last] == '(' && !left) {
						left = last;
					} else if (str[last] == ')' && left && !right) {
						right = last;
						break;
					}
				}
				if (left && right) {
					ext = str.substr(left + 1, right - left - 1);
				}
				if (cmd == "bg") {
					nextBackground = para;
				} else if (cmd == "ch") {
					nextCharacter = para;
				} else if (cmd == "jp") {
					tag = "{JUMP}";
					con = para;
				} else if (cmd == "sl") {
					std::regex pattern("\\{(.*?)(\\$.*?)\\}");
					for (std::sregex_iterator sit(para.cbegin(), para.cend(), pattern); sit != std::sregex_iterator(); sit++) {
						select.push_back(std::make_pair(sit->str(1), sit->str(2)));
					}
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

std::vector <std::pair <std::string, std::string>> Script::getSelect(void) {
	return script[pos].arguments;
}

void Script::jump(std::string flag) {
	for (unsigned i = 0; i < script.size(); i++) {
		if (script[i].name == "{FLAG}" && script[i].text == flag) {
			pos = i;
			return;
		}
	}
}

bool Script::next(void) {
	pos++;
	//std::cout << pos << ": " << script[pos].name << ", " << script[pos].text << (script[pos].select ? "S" : "N") << std::endl;
	//for (auto e : script[pos].arguments) {
	//	std::cout << e.first << "->" << e.second << "\n";
	//}
	if (pos >= script.size()) {
		return false;
	} else {
		if (script[pos].name == "{INFO}" || script[pos].name == "{FLAG}") {
			return next();
		} else if (script[pos].name == "{JUMP}") {
			jump(script[pos].text);
			return next();
		}
		return true;
	}
}