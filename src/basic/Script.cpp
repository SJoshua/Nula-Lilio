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
	script.push_back({ "{INFO}", filename });
	std::string str;
	Unit next;
	bool modifyBg = false, modifyCh = false, modifyBGM = false;

	while (std::getline(fs, str)) {
		if (str.empty()) {
			if (!next.text.empty()) {
				if (next.character == "-") {
					next.character.clear();
				}
				if (next.bgm == "-") {
					next.bgm.clear();
				}
				if (next.background == "-" || next.background.empty()) {
					next.background = "black";
				}
				if (!next.arguments.empty()) {
					next.select = true;
				}
				if (next.bgPos.empty()) {
					if (modifyBg || script.back().bgPos.empty()) {
						next.bgPos.push_back({ 0, 0 });
					} else {
						next.bgPos.push_back(script.back().bgPos.back());
					}
				}
				if (next.chPos.empty()) {
					if (modifyCh || script.back().chPos.empty()) {
						next.chPos.push_back({ 265, -100 });
					} else {
						next.chPos.push_back(script.back().chPos.back());
					}
				}
				script.push_back(next);
				next = { "", "", next.background, next.character, next.bgm };
				modifyBg = false, modifyCh = false, modifyBGM = false;
			}
		} else {
			if (str[0] == '#') {  // Comments
				continue;
			} else if (str[0] == '@') {  // Commands
				unsigned last = 0, begin = 0;
				for (; last < str.length(); last++) {
					if (str[last] == '[') {
						break;
					}
				}
				auto cmd = str.substr(1, last - 1);
				begin = last;
				for (; last < str.length(); last++) {
					if (str[last] == ']') {
						break;
					}
				}
				auto para = str.substr(begin + 1, last - begin - 1);
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
					next.background = para;
					modifyBg = true;
					int last = -1;
					if (!ext.empty()) {
						std::regex pattern("[\\-\\d+]+");
						for (std::sregex_iterator sit(ext.cbegin(), ext.cend(), pattern); sit != std::sregex_iterator(); sit++) {
							int num = std::stoi(sit->str(0));
							if (last != -1) {
								next.bgPos.push_back({last, num});
								last = -1;
							} else {
								last = num;
							}
						}
						if (last != -1) {
							next.bgSpeed = last;
						}
					}
				} else if (cmd == "ch") {
					next.character = para;
					modifyCh = true;
					int last = -1;
					if (!ext.empty()) {
						std::regex pattern("[\\-\\d+]+");
						for (std::sregex_iterator sit(ext.cbegin(), ext.cend(), pattern); sit != std::sregex_iterator(); sit++) {
							int num = std::stoi(sit->str(0));
							if (last != -1) {
								next.chPos.push_back({ last, num });
								last = -1;
							} else {
								last = num;
							}
						}
						if (last != -1) {
							next.chSpeed = last;
						}
					}
				} else if (cmd == "vo") {
					next.voice = para;
				} else if (cmd == "bgm") {
					next.bgm = para;
					modifyBGM = true;
				} else if (cmd == "jump") {
					next.name = "{JUMP}";
					next.text = para;
				} else if (cmd == "select") {
					std::regex pattern("\\{(.*?)(\\$.*?)\\}");
					for (std::sregex_iterator sit(para.cbegin(), para.cend(), pattern); sit != std::sregex_iterator(); sit++) {
						next.arguments.push_back(std::make_pair(sit->str(1), sit->str(2)));
					}
				} else {
					std::cout << "Unsupported command indicator: " << cmd << std::endl;
				}

			} else {
				if (next.name.empty()) {
					if (str[0] == '[') {
						for (unsigned int i = 0; i < str.length(); i++) {
							if (str[i] == ']') {
								next.name = str.substr(1, i - 1);
							}
						}
					}
				}
				for (unsigned int i = 0; i < str.length(); i++) {
					if (str[i] == '\t') {
						if (!next.text.empty()) {
							next.text += "\n";
						}
						next.text += str.substr(i + 1, str.length() - i - 1);
						break;
					} else if (str[i] == '$') {
						next.name = "{FLAG}";
						next.text = str.substr(i, str.length() - i + 2);
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

std::string Script::getVoice(void) {
	return script[pos].voice;
}

std::string Script::getBGM(void) {
	return script[pos].bgm;
}

std::string Script::getTag(void) {
	return tag;
}

unsigned int Script::getPosition(void) {
	return pos;
}

std::vector <Position> Script::getBackgroundPosition(void) {
	return script[pos].bgPos;
}

std::vector <Position> Script::getCharacterPosition(void) {
	return script[pos].chPos;
}

int Script::getBackgroundSpeed(void) {
	return script[pos].bgSpeed;
}

int Script::getCharacterSpeed(void) {
	return script[pos].chSpeed;
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
	//std::cout << pos << ": " << script[pos].background << " ";
	//for (auto e: script[pos].bgPos) {
	//	std::cout << "(" << e.x << ", " << e.y << ") ";
	//}
	//std::cout << "\n";
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