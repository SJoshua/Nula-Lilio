#include "basic/Engine.h"

SDL_Window *window = nullptr;
SDL_Surface *screen = nullptr;
SDL_Renderer *renderer = nullptr;

extern SceneManager scenes;
extern ResourceManager resources;

bool running = false;

Engine::Engine(void) {
	fps_mStartTicks = 0;
	fps_mPausedTicks = 0;
	fps_mPaused = false;
	fps_mStarted = false;

	cap_mStartTicks = 0;
	cap_mPausedTicks = 0;
	cap_mStarted = false;
	cap_mPaused = false;
}

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

	// Initialize SDL_Mixer
	flags = MIX_INIT_FLAC | MIX_INIT_MP3;
	if (!(Mix_Init(flags) & flags)) {
		std::cout << Mix_GetError() << std::endl;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cout << Mix_GetError() << std::endl;
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

	// Initialize Resource Manager
	resources.init();

	// Game Start!
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
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
}

void Engine::run(void) {
	running = true;

	int countedFrames = 0;

	while (running) {
		cap_mStarted = true;
		cap_mPaused = false;
		cap_mStartTicks = SDL_GetTicks();
		cap_mPausedTicks = 0;

		SDL_RenderClear(renderer);
		scenes.initFrame();
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			scenes.handle(e);
		}

		Uint32 time = 0;

		if (fps_mStarted) {
			if (fps_mPaused) {
				time = fps_mPausedTicks;
			} else {
				time = SDL_GetTicks() - fps_mStartTicks;
			}
		}

		float avgFPS = countedFrames / (time / 1000.f);
		if (avgFPS > 2000000) {
			avgFPS = 0;
		}

		scenes.update();
		scenes.render();
		SDL_RenderPresent(renderer);
		++countedFrames;

		time = 0;

		if (cap_mStarted) {
			if (cap_mPaused) {
				time = cap_mPausedTicks;
			} else {
				time = SDL_GetTicks() - cap_mStartTicks;
			}
		}

		int frameTicks = time;
		if (frameTicks < TICKS_PER_FRAME) {
			SDL_Delay(TICKS_PER_FRAME - frameTicks);
		}
	}
}