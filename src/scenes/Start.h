#ifndef SCENES_START_H
#define SCENES_START_H

#include "../Scene.h"
#include "../Scene_Manager.h"
#include "../Resource_Manager.h"
#include "../Texture.h"
#include "../Button.h"
#include "Dialogue.h"
#include "Exit.h"
#include "Load.h"

extern SceneManager scenes;
extern ResourceManager resources;
extern SDL_Renderer *renderer;

class Start: public Scene {
private:
	int current = 3; 
	// 0: Game Start
	// 1: Continue
	// 2: Exit
	Texture text;
	Button startBtn, continueBtn, exitBtn;

public:
	Start(void) {
		startBtn = Button(100, 200,
			resources.text(" Game Start ", resources.font("Coda.ttf", 60)),
			resources.text("<Game Start>", resources.font("Coda.ttf", 60))
		);
		
		continueBtn = Button(450, 250,
			resources.text(" Continue ", resources.font("Coda.ttf", 60)),
			resources.text("<Continue>", resources.font("Coda.ttf", 60))
		);
		
		exitBtn = Button(800, 300,
			resources.text(" Exit ", resources.font("Coda.ttf", 60)),
			resources.text("<Exit>", resources.font("Coda.ttf", 60))
		);
		
		text = Texture(560, 100, resources.text("Nula Lilio", resources.font("Deng.ttf", 100)));
	}

	void process(void) {
		if (current == 0) {
			scenes.jump(new Dialogue);
		} else if (current == 1) {
			scenes.jump(new Load);
		} else if (current == 2) {
			scenes.push(new Exit);
		}
		current = 3;
	}

	void onKeyDown(SDL_Keycode code) {
		// const Uint8 *currentKeyStates = SDL_GetKeyboardState(nullptr);
		// int step = currentKeyStates[SDL_SCANCODE_LSHIFT] ? 3 : 1;
		switch (code) {
			case SDLK_LEFT:
				(current += 2) %= 3;
				break;
			case SDLK_RIGHT:
				(current += 1) %= 3;
				break;
			case SDLK_RETURN:
				process();
		}
	}

	bool onMouseMove(int x, int y) {
		if (startBtn.isInside(x, y)) {
			current = 0;
		} else if (continueBtn.isInside(x, y)) {
			current = 1;
		} else if (exitBtn.isInside(x, y)) {
			current = 2;
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
		// int w, h;
		// SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
		SDL_RenderCopy(renderer, resources.picture("photo.jpg"), nullptr, nullptr);
		SDL_RenderCopy(renderer, text.getTexture(), nullptr, text.getRect());
		SDL_RenderCopy(renderer, current == 0 ? startBtn.getActive() : startBtn.getNormal(), nullptr, startBtn.getRect());
		SDL_RenderCopy(renderer, current == 1 ? continueBtn.getActive() : continueBtn.getNormal(), nullptr, continueBtn.getRect());
		SDL_RenderCopy(renderer, current == 2 ? exitBtn.getActive() : exitBtn.getNormal(), nullptr, exitBtn.getRect());
		
		// SDL_Rect rect = {x, y, w, h};
		// SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		// SDL_RenderFillRect(renderer, &rect);
		// SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
		// SDL_RenderDrawRect(renderer, &rect);
		// SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x3F);
		// SDL_RenderDrawLine(renderer, x, y, x + 20, y + 10);
		// SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0x3F);
		// SDL_RenderDrawPoint(renderer, x + 30, y + 30);
		// SDL_RenderCopy(renderer, resources.picture("photo.bmp"), nullptr, &rect);
		// SDL_RenderCopy(renderer, text, nullptr, &rect);
	}
};

#endif