#include "scenes/Save.h"

extern SceneManager scenes;
extern ResourceManager resources;
extern SDL_Renderer* renderer;

const int Gap = WINDOW_HEIGHT * 9 / 640;
const int Rect_width = (WINDOW_WIDTH * 9 / 10 - 4 * Gap) / 3;
const int Rect_height = (WINDOW_HEIGHT * 9 / 10 - 4 * Gap) / 3;
const int X0 = WINDOW_WIDTH * 5 / 100 + Gap;
const int Y0 = WINDOW_HEIGHT * 5 / 100 + Gap;

Save::Save(void) {
	returnBtn = Button(WINDOW_WIDTH / 10 * 8, WINDOW_HEIGHT / 100 * 94,
		resources.text(" Return ", resources.font(DEFAULT_FONT, 40)),
		resources.text("<Return>", resources.font(DEFAULT_FONT, 40))
	);

	Save_1Btn = Button(X0 + 5, Y0 + 5, resources.picture("save_1.jpg"), resources.picture("save_2.png"));
	Save_2Btn = Button(X0 + Gap + Rect_width + 5, Y0 + 5, resources.picture("save_1.jpg"), resources.picture("save_2.png"));
	Save_3Btn = Button(X0 + Gap * 2 + Rect_width * 2 + 5, Y0 + 5, resources.picture("save_1.jpg"), resources.picture("save_2.png"));
	Save_4Btn = Button(X0 + 5, Y0 + Gap + Rect_height + 5, resources.picture("save_1.jpg"), resources.picture("save_2.png"));
	Save_5Btn = Button(X0 + Gap + Rect_width + 5, Y0 + Gap + Rect_height + 5, resources.picture("save_1.jpg"), resources.picture("save_2.png"));
	Save_6Btn = Button(X0 + Gap * 2 + Rect_width * 2 + 5, Y0 + Gap + Rect_height + 5, resources.picture("save_1.jpg"), resources.picture("save_2.png"));
	Save_7Btn = Button(X0 + 5, Y0 + Gap * 2 + Rect_height * 2 + 5, resources.picture("save_1.jpg"), resources.picture("save_2.png"));
	Save_8Btn = Button(X0 + Gap + Rect_width + 5, Y0 + Gap * 2 + Rect_height * 2 + 5, resources.picture("save_1.jpg"), resources.picture("save_2.png"));
	Save_9Btn = Button(X0 + Gap * 2 + Rect_width * 2 + 5, Y0 + Gap * 2 + Rect_height * 2 + 5, resources.picture("save_1.jpg"), resources.picture("save_2.png"));

	data.resize(10);
	background = Texture(0, 0, resources.picture("save_3.jpg"));
	std::string sav = "00.sav", pic = "00.png";
	for (int i = 1; i <= 9; i++) {
		pic[1] = sav[1] = '0' + i;
		std::fstream fs(sav);
		if (!fs) {
			continue;
		}
		fs >> data[i].tag >> data[i].pos;
		data[i].pic = resources.picture(pic);
	}
}

void Save::process(void) {
	switch (current)
	{
	case 0:scenes.pop();
		break;
	case 1:scenes.push(new Saving);
		break;
	case 2:scenes.push(new Saving);
		break;
	case 3:scenes.push(new Saving);
		break;
	case 4:scenes.push(new Saving);
		break;
	case 5:scenes.push(new Saving);
		break;
	case 6:scenes.push(new Saving);
		break;
	case 7:scenes.push(new Saving);
		break;
	case 8:scenes.push(new Saving);
		break;
	case 9:scenes.push(new Saving);
		break;
	}
	current = 10;
}

bool Save::onMouseMove(int x, int y) {
	if (returnBtn.isInside(x, y)) {
		current = 0;
	}
	else if (Save_1Btn.isInside(x, y)) {
		current = 1;
	}
	else if (Save_2Btn.isInside(x, y)) {
		current = 2;
	}
	else if (Save_3Btn.isInside(x, y)) {
		current = 3;
	}
	else if (Save_4Btn.isInside(x, y)) {
		current = 4;
	}
	else if (Save_5Btn.isInside(x, y)) {
		current = 5;
	}
	else if (Save_6Btn.isInside(x, y)) {
		current = 6;
	}
	else if (Save_7Btn.isInside(x, y)) {
		current = 7;
	}
	else if (Save_8Btn.isInside(x, y)) {
		current = 8;
	}
	else if (Save_9Btn.isInside(x, y)) {
		current = 9;
	}
	else {
		return false;
	}
	return true;
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
	SDL_RenderCopy(renderer, background.getTexture(), nullptr, background.getRect());

	// Load Box
	SDL_Rect Save_1 = { X0, Y0, Rect_width, Rect_height };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &Save_1);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	SDL_RenderDrawRect(renderer, &Save_1);

	SDL_Rect Save_2 = { X0 + Gap + Rect_width, Y0, Rect_width, Rect_height };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &Save_2);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	SDL_RenderDrawRect(renderer, &Save_2);

	SDL_Rect Save_3 = { X0 + Gap * 2 + Rect_width * 2, Y0, Rect_width, Rect_height };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &Save_3);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	SDL_RenderDrawRect(renderer, &Save_3);

	SDL_Rect Save_4 = { X0, Y0 + Gap + Rect_height, Rect_width, Rect_height };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &Save_4);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	SDL_RenderDrawRect(renderer, &Save_4);

	SDL_Rect Save_5 = { X0 + Gap + Rect_width, Y0 + Gap + Rect_height, Rect_width, Rect_height };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &Save_5);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	SDL_RenderDrawRect(renderer, &Save_5);

	SDL_Rect Save_6 = { X0 + Gap * 2 + Rect_width * 2, Y0 + Gap + Rect_height, Rect_width, Rect_height };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &Save_6);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	SDL_RenderDrawRect(renderer, &Save_6);

	SDL_Rect Save_7 = { X0, Y0 + Gap * 2 + Rect_height * 2, Rect_width, Rect_height };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &Save_7);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	SDL_RenderDrawRect(renderer, &Save_7);

	SDL_Rect Save_8 = { X0 + Gap + Rect_width, Y0 + Gap * 2 + Rect_height * 2, Rect_width, Rect_height };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &Save_8);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	SDL_RenderDrawRect(renderer, &Save_8);

	SDL_Rect Save_9 = { X0 + Gap * 2 + Rect_width * 2, Y0 + Gap * 2 + Rect_height * 2, Rect_width, Rect_height };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &Save_9);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	SDL_RenderDrawRect(renderer, &Save_9);

	// Buttons
	SDL_RenderCopy(renderer, current == 0 ? returnBtn.getActive() : returnBtn.getNormal(), nullptr, returnBtn.getRect());
	SDL_RenderCopy(renderer, current == 1 ? Save_1Btn.getActive() : Save_1Btn.getNormal(), nullptr, Save_1Btn.getRect());
	SDL_RenderCopy(renderer, current == 2 ? Save_2Btn.getActive() : Save_2Btn.getNormal(), nullptr, Save_2Btn.getRect());
	SDL_RenderCopy(renderer, current == 3 ? Save_3Btn.getActive() : Save_3Btn.getNormal(), nullptr, Save_3Btn.getRect());
	SDL_RenderCopy(renderer, current == 4 ? Save_4Btn.getActive() : Save_4Btn.getNormal(), nullptr, Save_4Btn.getRect());
	SDL_RenderCopy(renderer, current == 5 ? Save_5Btn.getActive() : Save_5Btn.getNormal(), nullptr, Save_5Btn.getRect());
	SDL_RenderCopy(renderer, current == 6 ? Save_6Btn.getActive() : Save_6Btn.getNormal(), nullptr, Save_6Btn.getRect());
	SDL_RenderCopy(renderer, current == 7 ? Save_7Btn.getActive() : Save_7Btn.getNormal(), nullptr, Save_7Btn.getRect());
	SDL_RenderCopy(renderer, current == 8 ? Save_8Btn.getActive() : Save_8Btn.getNormal(), nullptr, Save_8Btn.getRect());
	SDL_RenderCopy(renderer, current == 9 ? Save_9Btn.getActive() : Save_9Btn.getNormal(), nullptr, Save_9Btn.getRect());

}
