#ifndef SCENES_DIALOGUE_H
#define SCENES_DIALOGUE_H

#include <SDL.h>
#include "../Scene.h"
#include "../Scene_Manager.h"
#include "../Resource_Manager.h"
#include "../Script.h"
#include "../Texture.h"

extern SceneManager scenes;
extern ResourceManager resources;
extern SDL_Renderer *renderer;

class Dialogue: public Scene {
private:
	Script *script;
	Texture background, character, text, name, delta;
	int tick = 0;

public:
	Dialogue(void) {
		script = new Script("begin.scr");
		background = Texture(0, 0, resources.picture(script->getBackground()));
		character = Texture(500, 0, resources.picture(script->getCharacter()));
		text = Texture(WINDOW_WIDTH * 12 / 100 , WINDOW_HEIGHT * 72 / 100,
			resources.text(script->getText(), resources.font("BIZ-UDMinchoM.ttc", 24))
		);
		name = Texture(WINDOW_WIDTH * 12 / 100, WINDOW_HEIGHT * 68 / 100,
			resources.text(script->getCharacterName(), resources.font("Coda.ttf", 24))
		);
		delta = Texture(WINDOW_WIDTH * 85 / 100 , WINDOW_HEIGHT * 85 / 100,
			resources.text("▼", resources.font("BIZ-UDMinchoM.ttc", 24))
		);
	}

	void update(void) {
		// Enter -> Next: Script.next
		// Else: Animation
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
		SDL_RenderCopy(renderer, background.getTexture(), nullptr, background.getRect());
		SDL_RenderCopy(renderer, character.getTexture(), nullptr, character.getRect());
		SDL_Rect rect = {WINDOW_WIDTH * 10 / 100, WINDOW_HEIGHT * 70 / 100, WINDOW_WIDTH * 80 / 100, WINDOW_HEIGHT * 20 / 100};
		SDL_SetRenderDrawColor(renderer, 0, 128, 192, 0xEF);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_RenderFillRect(renderer, &rect);
		SDL_Rect rect2 = {WINDOW_WIDTH * 11 / 100, WINDOW_HEIGHT * 67 / 100, WINDOW_WIDTH * 5 / 100, WINDOW_HEIGHT * 5 / 100};
		SDL_SetRenderDrawColor(renderer, 255, 201, 14, 0xBF);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_RenderFillRect(renderer, &rect2);
		SDL_RenderCopy(renderer, text.getTexture(), nullptr, text.getRect());
		SDL_RenderCopy(renderer, name.getTexture(), nullptr, name.getRect());
		SDL_RenderCopy(renderer, delta.getTexture(), nullptr, delta.getRect());
	}
};

#endif