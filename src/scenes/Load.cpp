#include "scenes/Load.h"

extern SceneManager scenes;
extern ResourceManager resources;
extern SDL_Renderer *renderer;

const int Gap = WINDOW_HEIGHT * 2 / 100;
const int Load_X = Gap;
const int Load_width = WINDOW_WIDTH / 2 - 2 * Gap;
const int Load_height = (WINDOW_HEIGHT - 10 * Gap) / 9;
const int pic_width = WINDOW_WIDTH * 45 / 100;
const int pic_height = WINDOW_HEIGHT * 45 / 100;
const int pic_X = WINDOW_WIDTH / 2 + Gap * 3;
const int pic_Y = (WINDOW_HEIGHT - pic_height) / 2;

Load::Load(void) {
	background = Texture(0, 0, resources.picture("blackboard.png"));

	title = Texture(0, 0, resources.text("Nula Lilio Savedata", resources.font(DEFAULT_FONT, 60)));
	loadLabel = Texture(WINDOW_WIDTH * 78 / 100, WINDOW_HEIGHT * 10 / 100, resources.text("- Load -", resources.font(DEFAULT_FONT, 40), { 0xFF, 0xFF, 0xFF }));

	backBtn = Button(WINDOW_WIDTH * 80 / 100, WINDOW_HEIGHT * 85 / 100,
		resources.text(" Back ", resources.font(DEFAULT_FONT, 40), { 0xFF, 0xFF, 0x9F }),
		resources.text("<Back>", resources.font(DEFAULT_FONT, 40), { 0xFF, 0xFF, 0x9F }));

	data.resize(10);
	buttons.resize(10);

	for (int i = 1; i <= 9; i++) {
		data[i].read(i);
	}

	for (int i = 1; i <= 9; i++) {
		buttons[i] = Button(WINDOW_WIDTH * 5 / 100, WINDOW_HEIGHT * 145 / 1000 + WINDOW_HEIGHT * 8 * (i - 1) / 100,
			resources.picture("white", WINDOW_WIDTH * 35 / 100, WINDOW_HEIGHT * 7 / 100),
			resources.text(data[i].getTime(), resources.font(DEFAULT_FONT, 22)));
	}
}

void Load::process(void) {
	if (current == 0) {
		scenes.pop();
		return;
	} else if (current <= 9) {
		if (data[current].pic) {
			scenes.pop();
			scenes.jump(new Dialogue(data[current].tag, data[current].pos));
		}
	}
}

bool Load::onMouseMove(int x, int y) {
	if (backBtn.isInside(x, y)) {
		current = 0;
		return true;
	} else {
		for (int i = 1; i <= 9; i++) {
			if (buttons[i].isInside(x, y)) {
				current = i;
				return true;
			}
		}
	}
	current = 10;
	return false;
}

void Load::onMouseDown(int x, int y) {
	if (onMouseMove(x, y)) {
		process();
	}
}

void Load::update(void) {
}

void Load::render(void) {
	// Background
	SDL_RenderCopy(renderer, background.getTexture(), nullptr, background.getRect());

	// Label
	SDL_RenderCopy(renderer, loadLabel.getTexture(), nullptr, loadLabel.getRect());

	// Box
	SDL_Rect rectScr = { WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 4, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
	SDL_Rect rectText = { rectScr.x + (rectScr.w - title.getRect()->w) / 2, rectScr.y + (rectScr.h - title.getRect()->h) / 2, title.getRect()->w, title.getRect()->h };
	if (current < 1 || current > 9 || !data[current].pic) {
		SDL_SetRenderDrawColor(renderer, 0xDF, 0xFF, 0xFF, 0xAF);
		SDL_RenderFillRect(renderer, &rectScr);
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(renderer, &rectScr);
		SDL_RenderCopy(renderer, title.getTexture(), nullptr, &rectText);
	}

	// Sub boxes
	for (int i = 1; i <= 9; i++) {
		SDL_Rect rect = {
			WINDOW_WIDTH * 5 / 100, WINDOW_HEIGHT * 145 / 1000 + WINDOW_HEIGHT * 8 * (i - 1) / 100,
			WINDOW_WIDTH * 35 / 100, WINDOW_HEIGHT * 7 / 100
		};
		if (current == i && data[current].timestamp) {
			if (data[current].pic) {
				SDL_RenderCopy(renderer, data[current].pic, nullptr, &rectScr);
			}
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xEF, 0xFF, 0xAF);
		} else {
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xAF, 0xAF);
		}
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderDrawRect(renderer, &rect);
	}

	// Buttons
	SDL_RenderCopy(renderer, current == 0 ? backBtn.getActive() : backBtn.getNormal(), nullptr, backBtn.getRect());
	for (int i = 1; i <= 9; i++) {
		SDL_Rect *tmp = Texture(0, 0, buttons[i].getActive()).getRect();
		SDL_Rect rect = {
			WINDOW_WIDTH * 5 / 100 + (WINDOW_WIDTH * 35 / 100 - tmp->w) / 2,
			WINDOW_HEIGHT * 145 / 1000 + WINDOW_HEIGHT * 8 * (i - 1) / 100 + (WINDOW_HEIGHT * 7 / 100 - tmp->h) / 2,
			tmp->w, tmp->h
		};
		SDL_RenderCopy(renderer, buttons[i].getActive(), nullptr, &rect);
	}
}
