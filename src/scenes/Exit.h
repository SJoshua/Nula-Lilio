#ifndef SCENES_EXIT_H
#define SCENES_EXIT_H

#include "../Config.h"
#include "../Scene.h"
#include "../Scene_Manager.h"
#include "../Resource_Manager.h"
#include "../Texture.h"
#include "../Button.h"

extern SceneManager scenes;
extern ResourceManager resources;
extern SDL_Renderer *renderer;

extern bool running;

class Exit: public Scene {
private:
	int current = 2;
	Button yesBtn, noBtn;
	Texture notice;
	
public:
	Exit(void) {
		yesBtn = Button(WINDOW_WIDTH / 10 * 3, WINDOW_HEIGHT / 10 * 5,
			resources.text(" Yes ", resources.font(DEFAULT_FONT, 60)),
			resources.text("[Yes]", resources.font(DEFAULT_FONT, 60))
		);

		noBtn = Button(WINDOW_WIDTH / 10 * 5, WINDOW_HEIGHT / 10 * 5,
			resources.text(" No ", resources.font(DEFAULT_FONT, 60)),
			resources.text("[No]", resources.font(DEFAULT_FONT, 60))
		);

		notice = Texture(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 10 * 3,
			resources.text("ゲームを終了します。\nよろしいですか？", resources.font(DEFAULT_FONT, 45))
		);
	}

	void process(void) {
		if (current == 0) {
			running = false;
		} else if (current == 1) {
			scenes.pop();
		}
		current = 2;
	}

	void onKeyDown(SDL_Keycode code) {
		switch (code) {
			case SDLK_LEFT: 
				current = 0;
				break;
			case SDLK_RIGHT:
				current = 1;
				break;
			case SDLK_RETURN:
				process();
				break;
		}
	}

	bool onMouseMove(int x, int y) {
		if (yesBtn.isInside(x, y)) {
			current = 0;
		} else if (noBtn.isInside(x, y)) {
			current = 1;
		} else {
			return false;
		}
		return true;
	}

	void onMouseDown(int x, int y) {
		if (onMouseMove(x, y)) {
			process();
		}
	}

	void update(void) {

	}

	void render(void) {
		SDL_Rect rect = {WINDOW_WIDTH / 5, WINDOW_HEIGHT / 5, WINDOW_WIDTH / 5 * 3, WINDOW_HEIGHT / 5 * 3};
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xEF);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderCopy(renderer, notice.getTexture(), nullptr, notice.getRect());
		SDL_RenderCopy(renderer, current == 0 ? yesBtn.getActive() : yesBtn.getNormal(), nullptr, yesBtn.getRect());
		SDL_RenderCopy(renderer, current == 1 ? noBtn.getActive() : noBtn.getNormal(), nullptr, noBtn.getRect());
	}
};

#endif