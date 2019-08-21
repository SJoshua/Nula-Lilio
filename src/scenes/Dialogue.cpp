#include "scenes/Dialogue.h"

extern SceneManager scenes;
extern ResourceManager resources;
extern SDL_Renderer *renderer;

Dialogue::Dialogue(std::string filename, int pos) {
	script = Script(filename, pos);
	processScript();
	delta = Texture(WINDOW_WIDTH * 85 / 100 , WINDOW_HEIGHT * 84 / 100,
		resources.text("▼", resources.font(DEFAULT_FONT, 24))
	);
	autoBtn = Button(WINDOW_WIDTH / 100 * 47, WINDOW_HEIGHT / 100 * 94,
		resources.text(" Auto ", resources.font(DEFAULT_FONT, 40)),
		resources.text("[Auto]", resources.font(DEFAULT_FONT, 40))
	);
	skipBtn = Button(WINDOW_WIDTH / 100 * 56, WINDOW_HEIGHT / 100 * 94,
		resources.text(" Skip ", resources.font(DEFAULT_FONT, 40)),
		resources.text("[Skip]", resources.font(DEFAULT_FONT, 40))
	);
	saveBtn = Button(WINDOW_WIDTH / 100 * 65, WINDOW_HEIGHT / 100 * 94,
		resources.text(" Save ", resources.font(DEFAULT_FONT, 40)),
		resources.text("[Save]", resources.font(DEFAULT_FONT, 40))
	);
	loadBtn = Button(WINDOW_WIDTH / 100 * 74, WINDOW_HEIGHT / 100 * 94,
		resources.text(" Load ", resources.font(DEFAULT_FONT, 40)),
		resources.text("[Load]", resources.font(DEFAULT_FONT, 40))
	);
	titleBtn = Button(WINDOW_WIDTH / 100 * 83, WINDOW_HEIGHT / 100 * 94,
		resources.text(" Title ", resources.font(DEFAULT_FONT, 40)),
		resources.text("[Title]", resources.font(DEFAULT_FONT, 40))
	);
}

void Dialogue::processScript(void) {
	if (!script.next()) {
		scenes.jump(new Start);
		return;
	}
	background = Texture(0, 0, resources.picture(script.getBackground()));
	if (!script.getCharacter().empty()) {
		showCharacter = true;
		character = Texture(265, -100, resources.picture(script.getCharacter()));
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

void Dialogue::onKeyDown(SDL_Keycode code) {
	switch (code) {
		case SDLK_RETURN:
		case SDLK_SPACE:
			//se.PlayChunk("test.wav"); 
			processScript();
			break;
	}
}

void Dialogue::processButtons(void) {
	if (current == 0) {
		// switch auto mode
		if (speed == 100) {
			speed = 0;
		} else {
			speed = 100;
		}
	} else if (current == 1) {
		// switch skip mode
		if (speed == 2) {
			speed = 0;
		} else {
			speed = 2;
		}
	} else if (current == 2) {
		scenes.push(new Save);
	} else if (current == 3) {
		scenes.push(new Load);
	} else if (current == 4) {
		scenes.jump(new Start);
	}
	current = 5;
}

bool Dialogue::onMouseMove(int x, int y) {
	if (autoBtn.isInside(x, y)) {
		current = 0;
		return true;
	} else if (skipBtn.isInside(x, y)) {
		current = 1;
		return true;
	} else if (saveBtn.isInside(x, y)) {
		current = 2;
		return true;
	} else if (loadBtn.isInside(x, y)) {
		current = 3;
		return true;
	} else if (titleBtn.isInside(x, y)) {
		current = 4;
		return true;
	} else {
		current = 5;
	}
	return false;
}

void Dialogue::onMouseDown(int x, int y) {
	if (onMouseMove(x, y)) {
		processButtons();
	} else {
		processScript();
	}
}

void Dialogue::update(void) {
	tick++;
	if (tick % 20 < 10) {
		delta.move(0, 1);
	} else if (tick % 20 < 20) {
		delta.move(0, -1);
	}
	if (speed) {
		if (tick % speed == 0) {
			processScript();
		}
	}
}

void Dialogue::render(void) {
	// Background
	SDL_RenderCopy(renderer, background.getTexture(), nullptr, background.getRect());
	// Character
	if (showCharacter) {
		SDL_RenderCopy(renderer, character.getTexture(), nullptr, character.getRect());
	}
	// Text Box
	SDL_Rect rect = {WINDOW_WIDTH * 10 / 100, WINDOW_HEIGHT * 70 / 100, WINDOW_WIDTH * 80 / 100, WINDOW_HEIGHT * 20 / 100};
	SDL_SetRenderDrawColor(renderer, 0, 128, 192, 0xCF);
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

	// Toolbar
	SDL_Rect rect3 = { WINDOW_WIDTH * 44 / 100, WINDOW_HEIGHT * 93 / 100, WINDOW_WIDTH * 46 / 100, WINDOW_HEIGHT * 6.5 / 100 };
	SDL_SetRenderDrawColor(renderer, 255, 174, 201, 0x5F);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &rect3);

	// Button
	SDL_RenderCopy(renderer, (current == 0 || speed == 100) ? autoBtn.getActive() : autoBtn.getNormal(), nullptr, autoBtn.getRect());
	SDL_RenderCopy(renderer, (current == 1 || speed == 2) ? skipBtn.getActive() : skipBtn.getNormal(), nullptr, skipBtn.getRect());
	SDL_RenderCopy(renderer, current == 2 ? saveBtn.getActive() : saveBtn.getNormal(), nullptr, saveBtn.getRect());
	SDL_RenderCopy(renderer, current == 3 ? loadBtn.getActive() : loadBtn.getNormal(), nullptr, loadBtn.getRect());
	SDL_RenderCopy(renderer, current == 4 ? titleBtn.getActive() : titleBtn.getNormal(), nullptr, titleBtn.getRect());
}
