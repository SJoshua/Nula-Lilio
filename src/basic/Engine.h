#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "basic/Scene.h"
#include "basic/Scene_Manager.h"
#include "basic/Resource_Manager.h"
#include "basic/Config.h"

#include "scenes/Start.h"
#include "scenes/Dialogue.h"

class Engine {
public:
    Engine (void);

	bool init(void);

	void start(void);

	void close(void);

	void run(void);
};

#endif