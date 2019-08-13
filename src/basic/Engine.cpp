#include "basic/Engine.h"

SDL_Window* window = nullptr;
SDL_Surface* screen = nullptr;
SDL_Renderer* renderer = nullptr;

extern SceneManager scenes;
extern ResourceManager resources;

bool running = false;

Engine::Engine (void) {}

bool Engine::init(void) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << SDL_GetError() << std::endl;
        return false; 
    }
    
    // Initialize SDL_Image
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!(IMG_Init(flags) & flags)) {
        std::cout << IMG_GetError() << std::endl;
    }

    // Initialize SDL_TTF
    if (TTF_Init() == -1) {
        std::cout << TTF_GetError() << std::endl;
    }

    // Create window
    window = SDL_CreateWindow("Nula Lilio", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Get the window screen
    screen = SDL_GetWindowSurface(window);

    start();

    return true;
}

void Engine::start(void) {
    scenes.push(new Start);
}

void Engine::close(void) {
    resources.free();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Engine::run(void) {
    running = true;
    while (running) {
        SDL_RenderClear(renderer);
        scenes.initFrame();
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            scenes.handle(e);
        }
        scenes.update();
        scenes.render();
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60);
    }
}