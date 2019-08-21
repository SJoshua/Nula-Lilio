#include "basic/Savedata.h"

Savedata::Savedata(void) {
	tag = "{NULL}";
	text = "PNULL";
	pic = nullptr;
	pos = 0;
	timestamp = 0;
}

Savedata::Savedata(std::string tag, std::string text, unsigned int pos, SDL_Texture* pic, time_t timestamp): tag(tag), text(text), pos(pos), pic(pic), timestamp(timestamp) {}

std::string Savedata::Serialize(void) {
	return "";
}

void Savedata::Unserialize(std::string) {

}

void Savedata::write(int stock) {
	std::ostringstream buffer;
	buffer << "save" << std::setw(2) << std::setfill('0') << stock << ".sav";
	std::string filename = buffer.str();
	std::ofstream os(filename, std::ios::binary);
	os << Serialize();
}

void Savedata::read(int stock) {
	std::ostringstream buffer;
	buffer << "save" << std::setw(2) << std::setfill('0') << stock << ".sav";
	std::string filename = buffer.str();
	std::ifstream is(filename, std::ios::binary);
	std::string data;
	is >> data;
	Unserialize(data);
}