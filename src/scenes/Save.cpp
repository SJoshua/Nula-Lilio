#include "scenes/Save.h"

extern SceneManager scenes;
extern ResourceManager resources;
extern SDL_Renderer* renderer;

const int Gap = WINDOW_HEIGHT * 9 / 640;
const int Rect_width = (WINDOW_WIDTH * 9 / 10 - 4 * Gap) / 3;
const int Rect_height = (WINDOW_HEIGHT * 9 / 10 - 4 * Gap) / 3;
const int X0 = WINDOW_WIDTH * 5 / 100 + Gap;
const int Y0 = WINDOW_HEIGHT * 5 / 100 + Gap;

Save::Save(Savedata state) : state(state) {
	backBtn = Button(WINDOW_WIDTH / 10 * 8, WINDOW_HEIGHT / 100 * 94,
		resources.text(" Back ", resources.font(DEFAULT_FONT, 40)),
		resources.text("<Back>", resources.font(DEFAULT_FONT, 40)));

	data.resize(10);

	for (int i = 1; i <= 9; i++) {
		data[i].read(i);
		if (data[i].pic == nullptr) {
			data[i].pic = resources.picture("save_1.jpg");
		}
	}

	buttons.resize(10);

	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			int i = 3 * x + y + 1;
			buttons[i] = Button(
				WINDOW_WIDTH * (85 + x * 290) / 1000, WINDOW_HEIGHT * (6 + y * 28) / 100,
				data[i].pic, nullptr);
		}
	}

	background = Texture(0, 0, resources.picture("photo_2.jpg"));
}

void Save::process(void) {
	if (current == 0) {
		scenes.pop();
		return;
	} else if (current <= 9) {
		data[current] = state;
		int x = (current - 1) / 3;
		int y = (current - 1) % 3;
		buttons[current] = Button(
			WINDOW_WIDTH * (85 + x * 290) / 1000, WINDOW_HEIGHT * (6 + y * 28) / 100,
			data[current].pic, nullptr);
		state.write(current);
	}
	current = 10;
}

bool Save::onMouseMove(int x, int y) {
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
	return false;
}

void Save::onMouseDown(int x, int y) {
	if (onMouseMove(x, y)) {
		process();
	}
}

void Save::update(void) {
}

void Save::render(void) {
	// Background
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	SDL_RenderClear(renderer);
	//SDL_RenderCopy(renderer, background.getTexture(), nullptr, background.getRect());

	// Box
	SDL_Rect rect_1 = {
		WINDOW_WIDTH * 3 / 100, WINDOW_HEIGHT * 3 / 100,
		WINDOW_WIDTH * 94 / 100, WINDOW_HEIGHT * 90 / 100
	};
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0xEF);
	SDL_RenderFillRect(renderer, &rect_1);

	// Sub boxes
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			SDL_Rect rect = {
				WINDOW_WIDTH * (85 + x * 290) / 1000, WINDOW_HEIGHT * (6 + y * 28) / 100,
				WINDOW_WIDTH * 25 / 100, WINDOW_HEIGHT * 25 / 100
			};
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
			SDL_RenderDrawRect(renderer, &rect);
		}
	}

	// Buttons
	SDL_RenderCopy(renderer, current == 0 ? backBtn.getActive() : backBtn.getNormal(), nullptr, backBtn.getRect());
	for (int i = 1; i <= 9; i++) {
		SDL_RenderCopy(renderer, buttons[i].getNormal(), nullptr, buttons[i].getRect());
	}
	//SDL_Rect Save_1 = { X0, Y0, Rect_width, Rect_height };
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	//SDL_RenderFillRect(renderer, &Save_1);
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	//SDL_RenderDrawRect(renderer, &Save_1);

	//SDL_Rect Save_2 = { X0 + Gap + Rect_width, Y0, Rect_width, Rect_height };
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	//SDL_RenderFillRect(renderer, &Save_2);
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	//SDL_RenderDrawRect(renderer, &Save_2);

	//SDL_Rect Save_3 = { X0 + Gap * 2 + Rect_width * 2, Y0, Rect_width, Rect_height };
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	//SDL_RenderFillRect(renderer, &Save_3);
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	//SDL_RenderDrawRect(renderer, &Save_3);

	//SDL_Rect Save_4 = { X0, Y0 + Gap + Rect_height, Rect_width, Rect_height };
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	//SDL_RenderFillRect(renderer, &Save_4);
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	//SDL_RenderDrawRect(renderer, &Save_4);

	//SDL_Rect Save_5 = { X0 + Gap + Rect_width, Y0 + Gap + Rect_height, Rect_width, Rect_height };
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	//SDL_RenderFillRect(renderer, &Save_5);
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	//SDL_RenderDrawRect(renderer, &Save_5);

	//SDL_Rect Save_6 = { X0 + Gap * 2 + Rect_width * 2, Y0 + Gap + Rect_height, Rect_width, Rect_height };
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	//SDL_RenderFillRect(renderer, &Save_6);
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	//SDL_RenderDrawRect(renderer, &Save_6);

	//SDL_Rect Save_7 = { X0, Y0 + Gap * 2 + Rect_height * 2, Rect_width, Rect_height };
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	//SDL_RenderFillRect(renderer, &Save_7);
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	//SDL_RenderDrawRect(renderer, &Save_7);

	//SDL_Rect Save_8 = { X0 + Gap + Rect_width, Y0 + Gap * 2 + Rect_height * 2, Rect_width, Rect_height };
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	//SDL_RenderFillRect(renderer, &Save_8);
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	//SDL_RenderDrawRect(renderer, &Save_8);

	//SDL_Rect Save_9 = { X0 + Gap * 2 + Rect_width * 2, Y0 + Gap * 2 + Rect_height * 2, Rect_width, Rect_height };
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	//SDL_RenderFillRect(renderer, &Save_9);
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	//SDL_RenderDrawRect(renderer, &Save_9);

	//// Buttons
	//SDL_RenderCopy(renderer, current == 0 ? returnBtn.getActive() : returnBtn.getNormal(), nullptr, returnBtn.getRect());
	//SDL_RenderCopy(renderer, current == 1 ? Save_1Btn.getActive() : Save_1Btn.getNormal(), nullptr, Save_1Btn.getRect());
	//SDL_RenderCopy(renderer, current == 2 ? Save_2Btn.getActive() : Save_2Btn.getNormal(), nullptr, Save_2Btn.getRect());
	//SDL_RenderCopy(renderer, current == 3 ? Save_3Btn.getActive() : Save_3Btn.getNormal(), nullptr, Save_3Btn.getRect());
	//SDL_RenderCopy(renderer, current == 4 ? Save_4Btn.getActive() : Save_4Btn.getNormal(), nullptr, Save_4Btn.getRect());
	//SDL_RenderCopy(renderer, current == 5 ? Save_5Btn.getActive() : Save_5Btn.getNormal(), nullptr, Save_5Btn.getRect());
	//SDL_RenderCopy(renderer, current == 6 ? Save_6Btn.getActive() : Save_6Btn.getNormal(), nullptr, Save_6Btn.getRect());
	//SDL_RenderCopy(renderer, current == 7 ? Save_7Btn.getActive() : Save_7Btn.getNormal(), nullptr, Save_7Btn.getRect());
	//SDL_RenderCopy(renderer, current == 8 ? Save_8Btn.getActive() : Save_8Btn.getNormal(), nullptr, Save_8Btn.getRect());
	//SDL_RenderCopy(renderer, current == 9 ? Save_9Btn.getActive() : Save_9Btn.getNormal(), nullptr, Save_9Btn.getRect());
}
