#ifndef SCENES_SAVE_H
#define SCENES_SAVE_H

#include <SDL.h>
#include <fstream>
#include <memory>
#include <vector>

#include "basic/Resource_Manager.h"
#include "basic/Savedata.h"
#include "basic/Scene.h"
#include "basic/Scene_Manager.h"

#include "ui/Button.h"
#include "ui/Texture.h"

#include "scenes/Confirm.h"
#include "scenes/Dialogue.h"

class Save: public Scene {
private:
	Texture background, title, saveLabel;
	std::vector <Savedata> data;
	std::vector <Button> buttons;
	Savedata state;
	bool callback = false;
	int current = 10, reg = 0;
	Button backBtn;

public:
	Save(Savedata data);

	void process(void);

	bool onMouseMove(int x, int y);

	void onMouseDown(int x, int y);

	void update(void);

	void render(void);

	void refresh(int specific = 0);
};

#endif