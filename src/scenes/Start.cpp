#include "scenes/Start.h"

extern SceneManager scenes;
extern ResourceManager resources;
extern SDL_Renderer *renderer;

Start::Start(void) {
	bgm.PlayMusic("test.mp3");

	startBtn = Button(400, 380,
		resources.text(" Game Start ", resources.font(DEFAULT_FONT, 40)),
		resources.text("<Game Start>", resources.font(DEFAULT_FONT, 40))
	);

	auto rect = startBtn.getRect();
	std::cout << rect->h << " " << rect->w << " " << rect->x << " " << rect->y << std::endl;

	continueBtn = Button(400, 440,
		resources.text(" Continue ", resources.font(DEFAULT_FONT, 40)),
		resources.text("<Continue>", resources.font(DEFAULT_FONT, 40))
	);
	
	configBtn = Button(400, 500,
		resources.text(" Config ", resources.font(DEFAULT_FONT, 40)),
		resources.text("<Config>", resources.font(DEFAULT_FONT, 40))
	);

	exitBtn = Button(400, 560,
		resources.text(" Exit ", resources.font(DEFAULT_FONT, 40)),
		resources.text("<Exit>", resources.font(DEFAULT_FONT, 40))
	);

	text = Texture(300, 180, resources.text("Nula Lilio", resources.font(DEFAULT_FONT, 100)));
}

void Start::process(void) {
	if (current == 0) {
		scenes.jump(new Dialogue);
	} else if (current == 1) {
		scenes.push(new Load);
	} else if (current == 3) {
		scenes.push(new Exit);
	}
	current = 4;
}

void Start::onKeyDown(SDL_Keycode code) {
	// const Uint8 *currentKeyStates = SDL_GetKeyboardState(nullptr);
	// int step = currentKeyStates[SDL_SCANCODE_LSHIFT] ? 4 : 1;
	switch (code) {
		case SDLK_RIGHT:
		case SDLK_DOWN:
			(current += 1) %= 5;
			break;
		case SDLK_LEFT:
		case SDLK_UP:
			(current += 4) %= 5;
			break;
		case SDLK_RETURN:
			process();
	}
}

bool Start::onMouseMove(int x, int y) {
	if (startBtn.isInside(x, y)) {
		current = 0;
	}else if (continueBtn.isInside(x, y)) {
		current = 1;
	}else if (configBtn.isInside(x, y)) {
		current = 2;
	}else if (exitBtn.isInside(x, y)) {
		current = 3;
	}else {
		current = 4;
		return false;
	}
	return true;
}

void Start::onMouseDown(int x, int y) {
	if (onMouseMove(x, y)) {
		process();
	}
}

void Start::update(void) {

}

void Start::render(void) {
	SDL_RenderCopy(renderer, resources.picture("photo_2.jpg"), nullptr, nullptr);
	SDL_RenderCopy(renderer, text.getTexture(), nullptr, text.getRect());
	SDL_RenderCopy(renderer, current == 0 ? startBtn.getActive() : startBtn.getNormal(), nullptr, startBtn.getRect());
	SDL_RenderCopy(renderer, current == 1 ? continueBtn.getActive() : continueBtn.getNormal(), nullptr, continueBtn.getRect());
	SDL_RenderCopy(renderer, current == 2 ? configBtn.getActive() : configBtn.getNormal(), nullptr, configBtn.getRect());
	SDL_RenderCopy(renderer, current == 3 ? exitBtn.getActive() : exitBtn.getNormal(), nullptr, exitBtn.getRect());
}
