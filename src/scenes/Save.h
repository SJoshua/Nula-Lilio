#ifndef SCENES_SAVE_H
#define SCENES_SAVE_H

#include <SDL.h>

#include "basic/Scene.h"
#include "basic/Scene_Manager.h"
#include "basic/Resource_Manager.h"

class Save: public Scene {
private:

public:
	Save (void);

	void update(void);

	void render(void);

};

#endif