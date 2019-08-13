#include "scenes/Start.h"

extern SceneManager scenes;
extern ResourceManager resources;
extern SDL_Renderer *renderer;

Start::Start(void) {
    startBtn = Button(100, 200,
        resources.text(" Game Start ", resources.font(DEFAULT_FONT, 60)),
        resources.text("<Game Start>", resources.font(DEFAULT_FONT, 60))
    );

	auto rect = startBtn.getRect();
	std::cout << rect->h << " " << rect->w << " " << rect->x << " " << rect->y << std::endl;

    continueBtn = Button(450, 250,
        resources.text(" Continue ", resources.font(DEFAULT_FONT, 60)),
        resources.text("<Continue>", resources.font(DEFAULT_FONT, 60))
    );
    
    exitBtn = Button(800, 300,
        resources.text(" Exit ", resources.font(DEFAULT_FONT, 60)),
        resources.text("<Exit>", resources.font(DEFAULT_FONT, 60))
    );
    
    text = Texture(560, 100, resources.text("Nula Lilio", resources.font(DEFAULT_FONT, 100)));
}

void Start::process(void) {
    if (current == 0) {
        scenes.push(new Dialogue);
    } else if (current == 1) {
        scenes.push(new Load);
    } else if (current == 2) {
        scenes.push(new Exit);
    }
    current = 3;
}

void Start::onKeyDown(SDL_Keycode code) {
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

bool Start::onMouseMove(int x, int y) {
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

void Start::onMouseDown(int x, int y) {
    if (onMouseMove(x, y)) {
        process();
    }
}

void Start::update(void) {

}

void Start::render(void) {
    SDL_RenderCopy(renderer, resources.picture("photo.jpg"), nullptr, nullptr);
    SDL_RenderCopy(renderer, text.getTexture(), nullptr, text.getRect());
    SDL_RenderCopy(renderer, current == 0 ? startBtn.getActive() : startBtn.getNormal(), nullptr, startBtn.getRect());
    SDL_RenderCopy(renderer, current == 1 ? continueBtn.getActive() : continueBtn.getNormal(), nullptr, continueBtn.getRect());
    SDL_RenderCopy(renderer, current == 2 ? exitBtn.getActive() : exitBtn.getNormal(), nullptr, exitBtn.getRect());
}
