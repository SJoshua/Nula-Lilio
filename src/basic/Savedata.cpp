#include "basic/Savedata.h"

extern ResourceManager resources;
extern SDL_Renderer* renderer;

Savedata::Savedata(void) {
	tag = "{NULL}";
	text = "{NULL}";
	pic = nullptr;
	pos = 0;
	timestamp = 0;
}

Savedata::Savedata(std::string tag, std::string text, unsigned int pos, SDL_Texture* pic, time_t timestamp) : tag(tag), text(text), pos(pos), pic(pic), timestamp(timestamp) {}

std::string Savedata::serialize(void) {
	std::ostringstream buffer;
	buffer << tag << std::endl
		   << pos << std::endl
		   << timestamp << std::endl;
	return buffer.str();
}

void Savedata::unserialize(std::string str) {
	std::istringstream buffer(str);
	buffer >> tag >> pos >> timestamp;
}

void Savedata::write(int stock) {
	std::ostringstream buffer;
	buffer << "savedata/save" << std::setw(2) << std::setfill('0') << stock;

	// Write Savedata
	std::string filename = buffer.str();
	std::ofstream os(filename + ".sav", std::ios::binary);
	os << serialize();

	// Save Screenshot
	int width, height;
	SDL_SetRenderTarget(renderer, pic);
	SDL_QueryTexture(pic, nullptr, nullptr, &width, &height);
	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	SDL_RenderReadPixels(renderer, nullptr, surface->format->format, surface->pixels, surface->pitch);
	IMG_SavePNG(surface, (filename + ".png").c_str());
	SDL_FreeSurface(surface);
	SDL_SetRenderTarget(renderer, nullptr);
}

void Savedata::read(int stock) {
	std::ostringstream buffer;
	buffer << "savedata/save" << std::setw(2) << std::setfill('0') << stock;
	std::string filename = buffer.str();
	std::ifstream is(filename + ".sav", std::ios::binary);
	if (is) {
		std::string data;
		is >> data;
		if (!data.empty()) {
			unserialize(data);
			pic = resources.picture("../../" + filename + ".png", true);
		}
	}
}