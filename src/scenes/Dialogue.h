#ifndef SCENES_DIALOGUE_H
#define SCENES_DIALOGUE_H

#include <SDL.h>
#include <string>
#include "../Scene.h"
#include "../Scene_Manager.h"
#include "../Resource_Manager.h"
#include "../Config.h"
#include "../Script.h"
#include "../Texture.h"

extern SceneManager scenes;
extern ResourceManager resources;
extern SDL_Renderer *renderer;

class Dialogue: public Scene {
private:
	Script script;
	Texture background, character, text, name, delta;
	bool showCharacter, showName;
	int tick = 0;

public:
	Dialogue(void) {
		script = Script("prologue.nls");
		process();
		delta = Texture(WINDOW_WIDTH * 85 / 100 , WINDOW_HEIGHT * 85 / 100,
			resources.text("▼", resources.font(DEFAULT_FONT, 24))
		);
	}

	void process(void) {
		script.next();
		background = Texture(0, 0, resources.picture(script.getBackground()));
		if (!script.getCharacter().empty()) {
			showCharacter = true;
			character = Texture(500, 0, resources.picture(script.getCharacter()));
		} else {
			showCharacter = false;
		}
		text = Texture(WINDOW_WIDTH * 12 / 100 , WINDOW_HEIGHT * 72 / 100,
			resources.text(script.getText(), resources.font(DEFAULT_FONT, 24))
		);
		if (!script.getCharacterName().empty()) {
			showName = true;
			name = Texture(WINDOW_WIDTH * 12 / 100, WINDOW_HEIGHT * 64 / 100,
				resources.text(script.getCharacterName(), resources.font(DEFAULT_FONT, 24))
			);
		} else {
			showName = false;
		}
	}

	void onKeyDown(SDL_Keycode code) {
		switch (code) {
			case SDLK_RETURN:
				process();
				break;
		}
	}

	void update(void) {
		tick++;
		if (tick < 10) {
			delta.move(0, 1);
		} else if (tick < 20) {
			delta.move(0, -1);
		} else {
			tick = -1;
		}
	}

	void render(void) {
		// Background
		SDL_RenderCopy(renderer, background.getTexture(), nullptr, background.getRect());
		// Character
		if (showCharacter) {
			SDL_RenderCopy(renderer, character.getTexture(), nullptr, character.getRect());
		}
		// Text Box
		SDL_Rect rect = {WINDOW_WIDTH * 10 / 100, WINDOW_HEIGHT * 70 / 100, WINDOW_WIDTH * 80 / 100, WINDOW_HEIGHT * 20 / 100};
		SDL_SetRenderDrawColor(renderer, 0, 128, 192, 0xEF);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_RenderFillRect(renderer, &rect);
		// Name
		if (showName) {
			SDL_Rect rect2 = {WINDOW_WIDTH * 11 / 100, WINDOW_HEIGHT * 63 / 100, WINDOW_WIDTH * 10 / 100, WINDOW_HEIGHT * 6 / 100};
			SDL_SetRenderDrawColor(renderer, 255, 201, 14, 0xBF);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rect2);
			SDL_RenderCopy(renderer, name.getTexture(), nullptr, name.getRect());
		}
		SDL_RenderCopy(renderer, text.getTexture(), nullptr, text.getRect());
		SDL_RenderCopy(renderer, delta.getTexture(), nullptr, delta.getRect());
	}
};

#endif
