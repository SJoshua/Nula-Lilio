#include "scenes/Dialogue.h"

extern SceneManager scenes;
extern ResourceManager resources;
extern SDL_Renderer *renderer;

Dialogue::Dialogue(std::string filename, int pos) {
	script = Script(filename, pos);
	process();
	delta = Texture(WINDOW_WIDTH * 85 / 100 , WINDOW_HEIGHT * 84 / 100,
		resources.text("▼", resources.font(DEFAULT_FONT, 24))
	);
	saveBtn = Button(WINDOW_WIDTH / 10 * 7, WINDOW_HEIGHT / 100 * 94,
		resources.text(" Save ", resources.font(DEFAULT_FONT, 40)),
		resources.text("<Save>", resources.font(DEFAULT_FONT, 40))
	);
	returnBtn = Button(WINDOW_WIDTH / 10 * 8, WINDOW_HEIGHT / 100 * 94,
		resources.text(" Return ", resources.font(DEFAULT_FONT, 40)),
		resources.text("<Return>", resources.font(DEFAULT_FONT, 40))
	);
}

void Dialogue::process(void) {
	if (!script.next()) {
		scenes.jump(new Start);
		return;
	}
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

void Dialogue::onKeyDown(SDL_Keycode code) {
	switch (code) {
		case SDLK_RETURN:
		case SDLK_SPACE:
			se.PlayChunk("test.wav"); process();
			break;
	}
}

void Dialogue::Button_process(void) {
	if (current == 0) {
		scenes.push(new Save);
	}
	else if (current == 1) {
		scenes.jump(new Start);
	}
	current = 2;
}

bool Dialogue::onMouseMove(int x, int y) {
	if (saveBtn.isInside(x, y)) {
		current = 0;
	}else if (returnBtn.isInside(x, y)) {
		current = 1;
	} else {
		current = 2;
		return false;
	}
	return true;
}

void Dialogue::onMouseDown(int x, int y) {
	if (onMouseMove(x, y)) {
		Button_process();
	}
}

void Dialogue::update(void) {
	tick++;
	if (tick < 10) {
		delta.move(0, 1);
	} else if (tick < 20) {
		delta.move(0, -1);
	} else {
		tick = -1;
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
	// Button
	SDL_RenderCopy(renderer, current == 0 ? saveBtn.getActive() : saveBtn.getNormal(), nullptr, saveBtn.getRect());
	SDL_RenderCopy(renderer, current == 1 ? returnBtn.getActive() : returnBtn.getNormal(), nullptr, returnBtn.getRect());

}
