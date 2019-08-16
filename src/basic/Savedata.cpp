#include "basic/Savedata.h"

Savedata::Savedata(std::string tag, std::string text, unsigned int pos, SDL_Texture* pic, time_t timestamp): tag(tag), text(text), pos(pos), pic(pic), timestamp(timestamp) {}