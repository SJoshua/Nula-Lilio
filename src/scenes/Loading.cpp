#include "Loading.h"

extern SceneManager scenes;
extern ResourceManager resources;
extern SDL_Renderer *renderer;

Loading::Loading(void) {
	yesBtn = Button(WINDOW_WIDTH / 10 * 3, WINDOW_HEIGHT / 10 * 6,
		resources.text(" Yes ", resources.font(DEFAULT_FONT, 60)),
		resources.text("[Yes]", resources.font(DEFAULT_FONT, 60)));

	noBtn = Button(WINDOW_WIDTH / 20 * 11, WINDOW_HEIGHT / 10 * 6,
		resources.text(" No ", resources.font(DEFAULT_FONT, 60)),
		resources.text("[No]", resources.font(DEFAULT_FONT, 60)));

	notice = Texture(WINDOW_WIDTH * 27 / 100, WINDOW_HEIGHT / 10 * 3,
		resources.text("データをロードしますか？", resources.font(DEFAULT_FONT, 45)));
}

void Loading::process(void) {
	if (current == 1) {
		scenes.pop();
	}
	current = 2;
}

void Loading::onKeyDown(SDL_Keycode code) {
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

bool Loading::onMouseMove(int x, int y) {
	if (yesBtn.isInside(x, y)) {
		current = 0;
	} else if (noBtn.isInside(x, y)) {
		current = 1;
	} else {
		return false;
	}
	return true;
}

void Loading::onMouseDown(int x, int y) {
	if (onMouseMove(x, y)) {
		process();
	}
}

void Loading::update(void) {
}

void Loading::render(void) {
	SDL_Rect rect = { WINDOW_WIDTH / 5, WINDOW_HEIGHT / 5, WINDOW_WIDTH / 5 * 3, WINDOW_HEIGHT / 5 * 3 };
	SDL_SetRenderDrawColor(renderer, 255, 231, 186, 0xEF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderCopy(renderer, notice.getTexture(), nullptr, notice.getRect());
	SDL_RenderCopy(renderer, current == 0 ? yesBtn.getActive() : yesBtn.getNormal(), nullptr, yesBtn.getRect());
	SDL_RenderCopy(renderer, current == 1 ? noBtn.getActive() : noBtn.getNormal(), nullptr, noBtn.getRect());
}