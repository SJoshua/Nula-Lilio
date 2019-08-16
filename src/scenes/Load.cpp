#include "scenes/Load.h"

extern SceneManager scenes;
extern ResourceManager resources;
extern SDL_Renderer* renderer;

const int Gap = WINDOW_HEIGHT * 9 / 640;
const int Rect_width = (WINDOW_WIDTH * 9 / 10 - 4 * Gap) / 3;
const int Rect_height = (WINDOW_HEIGHT * 9 / 10 - 4 * Gap) / 3;
const int X0 = WINDOW_WIDTH * 5 / 100 + Gap;
const int Y0 = WINDOW_HEIGHT * 5 / 100 + Gap;

Load::Load(void) {
	returnBtn = Button(WINDOW_WIDTH / 10 * 8, WINDOW_HEIGHT / 100 * 94,
		resources.text(" Return ", resources.font(DEFAULT_FONT, 40)),
		resources.text("<Return>", resources.font(DEFAULT_FONT, 40))
	);

	Load_1Btn = Button(X0 + 5, Y0 + 5, resources.picture("load_1.jpg"), resources.picture("load_2.png"));
	Load_2Btn = Button(X0 + Gap + Rect_width + 5, Y0 + 5, resources.picture("load_1.jpg"), resources.picture("load_2.png"));
	Load_3Btn = Button(X0 + Gap * 2 + Rect_width * 2 + 5, Y0 + 5, resources.picture("load_1.jpg"), resources.picture("load_2.png"));
	Load_4Btn = Button(X0 + 5, Y0 + Gap + Rect_height + 5, resources.picture("load_1.jpg"), resources.picture("load_2.png"));
	Load_5Btn = Button(X0 + Gap + Rect_width + 5, Y0 + Gap + Rect_height + 5, resources.picture("load_1.jpg"), resources.picture("load_2.png"));
	Load_6Btn = Button(X0 + Gap * 2 + Rect_width * 2 + 5, Y0 + Gap + Rect_height + 5, resources.picture("load_1.jpg"), resources.picture("load_2.png"));
	Load_7Btn = Button(X0 + 5, Y0 + Gap * 2 + Rect_height * 2 + 5, resources.picture("load_1.jpg"), resources.picture("load_2.png"));
	Load_8Btn = Button(X0 + Gap + Rect_width + 5, Y0 + Gap * 2 + Rect_height * 2 + 5, resources.picture("load_1.jpg"), resources.picture("load_2.png"));
	Load_9Btn = Button(X0 + Gap * 2 + Rect_width * 2 + 5, Y0 + Gap * 2 + Rect_height * 2 + 5, resources.picture("load_1.jpg"), resources.picture("load_2.png"));

	data.resize(10);
	background = Texture(0, 0, resources.picture("load_3.jpg"));
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

void Load::process(void) {
	switch (current)
	{
	case 0:scenes.pop();
		break;
	case 1:scenes.push(new Loading);
		break;
	case 2:scenes.push(new Loading);
		break;
	case 3:scenes.push(new Loading);
		break;
	case 4:scenes.push(new Loading);
		break;
	case 5:scenes.push(new Loading);
		break;
	case 6:scenes.push(new Loading);
		break;
	case 7:scenes.push(new Loading);
		break;
	case 8:scenes.push(new Loading);
		break;
	case 9:scenes.push(new Loading);
		break;
	}
	current = 10;
}

bool Load::onMouseMove(int x, int y) {
	if (returnBtn.isInside(x, y)) {
		current = 0;
	}else if (Load_1Btn.isInside(x, y)) {
		current = 1;
	}else if (Load_2Btn.isInside(x, y)) {
		current = 2;
	}else if (Load_3Btn.isInside(x, y)) {
		current = 3;
	}else if (Load_4Btn.isInside(x, y)) {
		current = 4;
	}else if (Load_5Btn.isInside(x, y)) {
		current = 5;
	}else if (Load_6Btn.isInside(x, y)) {
		current = 6;
	}else if (Load_7Btn.isInside(x, y)) {
		current = 7;
	}else if (Load_8Btn.isInside(x, y)) {
		current = 8;
	}else if (Load_9Btn.isInside(x, y)) {
		current = 9;
	}else {
		return false;
	}
	return true;
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

	// Load Box
	SDL_Rect Load_1 = { X0, Y0, Rect_width, Rect_height };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &Load_1);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	SDL_RenderDrawRect(renderer, &Load_1);

	SDL_Rect Load_2 = { X0 + Gap + Rect_width, Y0, Rect_width, Rect_height };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &Load_2);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	SDL_RenderDrawRect(renderer, &Load_2);

	SDL_Rect Load_3 = { X0 + Gap * 2 + Rect_width * 2, Y0, Rect_width, Rect_height };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &Load_3);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	SDL_RenderDrawRect(renderer, &Load_3);

	SDL_Rect Load_4 = { X0, Y0 + Gap + Rect_height, Rect_width, Rect_height };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &Load_4);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	SDL_RenderDrawRect(renderer, &Load_4);

	SDL_Rect Load_5 = { X0 + Gap + Rect_width, Y0 + Gap + Rect_height, Rect_width, Rect_height };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &Load_5);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	SDL_RenderDrawRect(renderer, &Load_5);

	SDL_Rect Load_6 = { X0 + Gap * 2 + Rect_width * 2, Y0 + Gap + Rect_height, Rect_width, Rect_height };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &Load_6);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	SDL_RenderDrawRect(renderer, &Load_6);

	SDL_Rect Load_7 = { X0, Y0 + Gap * 2 + Rect_height * 2, Rect_width, Rect_height };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &Load_7);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	SDL_RenderDrawRect(renderer, &Load_7);

	SDL_Rect Load_8 = { X0 + Gap + Rect_width, Y0 + Gap * 2 + Rect_height * 2, Rect_width, Rect_height };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &Load_8);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	SDL_RenderDrawRect(renderer, &Load_8);

	SDL_Rect Load_9 = { X0 + Gap * 2 + Rect_width * 2, Y0 + Gap * 2 + Rect_height * 2, Rect_width, Rect_height };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xEF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &Load_9);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xEF);
	SDL_RenderDrawRect(renderer, &Load_9);

	// Buttons
	SDL_RenderCopy(renderer, current == 0 ? returnBtn.getActive() : returnBtn.getNormal(), nullptr, returnBtn.getRect());
	SDL_RenderCopy(renderer, current == 1 ? Load_1Btn.getActive() : Load_1Btn.getNormal(), nullptr, Load_1Btn.getRect());
	SDL_RenderCopy(renderer, current == 2 ? Load_2Btn.getActive() : Load_2Btn.getNormal(), nullptr, Load_2Btn.getRect());
	SDL_RenderCopy(renderer, current == 3 ? Load_3Btn.getActive() : Load_3Btn.getNormal(), nullptr, Load_3Btn.getRect());
	SDL_RenderCopy(renderer, current == 4 ? Load_4Btn.getActive() : Load_4Btn.getNormal(), nullptr, Load_4Btn.getRect());
	SDL_RenderCopy(renderer, current == 5 ? Load_5Btn.getActive() : Load_5Btn.getNormal(), nullptr, Load_5Btn.getRect());
	SDL_RenderCopy(renderer, current == 6 ? Load_6Btn.getActive() : Load_6Btn.getNormal(), nullptr, Load_6Btn.getRect());
	SDL_RenderCopy(renderer, current == 7 ? Load_7Btn.getActive() : Load_7Btn.getNormal(), nullptr, Load_7Btn.getRect());
	SDL_RenderCopy(renderer, current == 8 ? Load_8Btn.getActive() : Load_8Btn.getNormal(), nullptr, Load_8Btn.getRect());
	SDL_RenderCopy(renderer, current == 9 ? Load_9Btn.getActive() : Load_9Btn.getNormal(), nullptr, Load_9Btn.getRect());

}
