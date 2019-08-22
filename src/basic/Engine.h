#ifndef BASIC_ENGINE_H
#define BASIC_ENGINE_H

#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

#include "basic/Scene.h"
#include "basic/Scene_Manager.h"
#include "basic/Resource_Manager.h"
#include "basic/Config.h"

#include "scenes/Start.h"
#include "scenes/Dialogue.h"

class Engine {
private:
	Uint32 cap_mStartTicks, fps_mStartTicks;
	Uint32 cap_mPausedTicks, fps_mPausedTicks;
	bool cap_mPaused, fps_mPaused;
	bool cap_mStarted, fps_mStarted;
	std::stringstream timeText;

public:
	Engine (void);

	bool init(void);

	void start(void);

	void close(void);

	void run(void);
};

#endif