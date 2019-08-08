/* Project Nula Lilio
 * Au: SJoshua
 */
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <deque>
#include <set>

SDL_Window *window = nullptr;
SDL_Surface *screen = nullptr;
SDL_Renderer *renderer = nullptr;

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;
const int FPS = 60;
const int TICKS_PER_FRAME = 1000 / FPS;

bool running = false;

class Scene {
public:
	virtual void initFrame(void) {}
	virtual void onKeyDown(SDL_Keycode code) {}
	virtual void onMouseDown(int x, int y) {}
	virtual bool onMouseMove(int x, int y) {}
	virtual void update(void) = 0;
	virtual void render(void) = 0;
};


class SceneManager {
private:
	std::deque <Scene*> list;

public:
	void push(Scene *scene) {
		list.push_back(scene);
	}

	void pop(void) {
		list.pop_back();
	}
	
	Scene* top(void) {
		return list.back();
	}

	void jump(Scene* scene) {
		Scene *s = top();
		pop();
		push(scene);
		delete s;		
	}

	void initFrame(void) {
		for (auto s: list) {
			s->initFrame();
		}
	}

	void handle(SDL_Event &e) {
		for (auto s: list) {
			if (e.type == SDL_QUIT) {
				running = false;
			} else if (e.type == SDL_KEYDOWN) {
				top()->onKeyDown(e.key.keysym.sym);
			} else if (e.type == SDL_MOUSEMOTION) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				top()->onMouseMove(x, y);
			} else if (e.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				top()->onMouseDown(x, y);
			} else {
				// To-do
			}
		}
	}

	void update(void) {
		for (auto s: list) {
			s->update();
		}
	}

	void render(void) {
		for (auto s: list) {
			s->render();
		}
	}
} scenes;

class Texture {
private:
	SDL_Texture *texture;
	SDL_Rect rect;
public:
	Texture(void) {}
	Texture(int x, int y, SDL_Texture *texture): texture(texture) {
		rect.x = x;
		rect.y = y;
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	}
	void move(int dx, int dy) {
		rect.x += dx;
		rect.y += dy;
	}
	SDL_Texture* getTexture(void) {
		return texture;
	}
	SDL_Rect* getRect(void) {
		return &rect;
	}
	bool isInside(int px, int py) {
		return (rect.x <= px && px <= rect.x + rect.w && rect.y <= py && py <= rect.y + rect.h);
	}
};

class Button {
private:
	SDL_Texture *normal, *active;
	SDL_Rect rect;
public:
	Button(void) {}
	Button(int x, int y, SDL_Texture *normal, SDL_Texture *active): normal(normal), active(active) {
		rect.x = x;
		rect.y = y;
		SDL_QueryTexture(normal, nullptr, nullptr, &rect.w, &rect.h);
	}
	SDL_Texture* getNormal(void) {
		return normal;
	}
	SDL_Texture* getActive(void) {
		return active;
	}
	SDL_Rect* getRect(void) {
		return &rect;
	}
	bool isInside(int px, int py) {
		return (rect.x <= px && px <= rect.x + rect.w && rect.y <= py && py <= rect.y + rect.h);
	}
	// SDL_Texture* getTexture(int px, int py) {
	// 	if (x <= px && px <= x + w && y <= py && py <= y + h) {
	// 		return active;
	// 	} else {
	// 		return normal;
	// 	}
	// }
};

class ResourceManager {
private:
	std::unordered_map <std::string, SDL_Texture*> pictures;
	std::unordered_map <std::string, SDL_Surface*> audios;
	std::unordered_map <std::string, std::unordered_map <int, TTF_Font*>> fonts;
	
	SDL_Texture* loadPicture(std::string path) {
		SDL_Surface *surface = IMG_Load(path.c_str());
		SDL_Texture *texture = nullptr;
		if (surface == nullptr) {
			std::cout << IMG_GetError() << std::endl;
		} else {
			texture = SDL_CreateTextureFromSurface(renderer, surface);
			if (texture == nullptr) {
				std::cout << SDL_GetError() << std::endl;
			}
			SDL_FreeSurface(surface);
		}		
		return texture;
	}

	TTF_Font* loadFont(std::string path, int size) {
		TTF_Font *font = TTF_OpenFont(path.c_str(), size);
		if (font == nullptr) {
			std::cout << TTF_GetError() << std::endl;
		} 
		return font;
	}

public:
	TTF_Font* font(std::string filename, int size) {
		std::string path = "resource/fonts/" + filename;
		if (!fonts[filename].count(size)) {
			auto font = loadFont(path, size);
			if (font == nullptr) {
				std::cout << "[Failed] load font: " << path << std::endl;
			} else {
				fonts[filename][size] = font;
			}
		}
		return fonts[filename][size];
	}

	SDL_Texture* picture(std::string filename) {
		std::string path = "resource/pictures/" + filename;
		if (!pictures.count(filename)) {
			auto pic = loadPicture(path);
			if (pic == nullptr) {
				std::cout << "[Failed] load picture: " << path << std::endl;
			} else {
				pictures[filename] = pic;
			}
		}
		return pictures[filename];
	}

	SDL_Texture* text(std::string text, TTF_Font *font, SDL_Color color = {0, 0, 0}) {
		auto *surface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), color, WINDOW_WIDTH);
		auto *texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		return texture;
	}

	void free(void) {
		for (auto e: pictures) {
			SDL_DestroyTexture(e.second);
		}
		for (auto e: audios) {
			// To-do
		}
		for (auto e: fonts) {
			for (auto s: e.second) {
				TTF_CloseFont(s.second);
			}
		}
	}
} resources;


class Script {
private:
	std::string text, name;
	Texture background, character;
public:
	Script(void) {}

	Script(std::string filename) {
		text = "これは脚本ですよーっと。\n頑張ってね！";
		name = "Rin";
		background = Texture(0, 0, resources.picture("background.jpg"));
		character = Texture(500, 20, resources.picture("character.png"));
	}

	std::string getCharacterName(void) {
		return name;
	}

	std::string getText(void) {
		return text;
	}

	Texture getBackground(void) {
		return background;
	}

	Texture getCharacter(void) {
		return character;
	}	
};

class Load: public Scene {
private:
public:
	void update(void) {

	}

	void render(void) {

	}
};

class Save: public Scene {
private:
public:
	void update(void) {

	}

	void render(void) {
		
	}
};

class Exit: public Scene {
private:
	int current = 2;
	Button yesBtn, noBtn;
	Texture notice;
public:
	Exit(void) {
		yesBtn = Button(WINDOW_WIDTH / 10 * 3, WINDOW_HEIGHT / 10 * 5,
			resources.text(" Yes ", resources.font("Coda.ttf", 60)),
			resources.text("[Yes]", resources.font("Coda.ttf", 60))
		);

		noBtn = Button(WINDOW_WIDTH / 10 * 5, WINDOW_HEIGHT / 10 * 5,
			resources.text(" No ", resources.font("Coda.ttf", 60)),
			resources.text("[No]", resources.font("Coda.ttf", 60))
		);

		notice = Texture(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 10 * 3,
			resources.text("ゲームを終了します。\nよろしいですか？", resources.font("BIZ-UDMinchoM.ttc", 45))
		);
	}

	void process(void) {
		if (current == 0) {
			running = false;
		} else if (current == 1) {
			scenes.pop();
		}
		current = 2;
	}

	void onKeyDown(SDL_Keycode code) {
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

	bool onMouseMove(int x, int y) {
		if (yesBtn.isInside(x, y)) {
			current = 0;
		} else if (noBtn.isInside(x, y)) {
			current = 1;
		} else {
			return false;
		}
		return true;
	}

	void onMouseDown(int x, int y) {
		if (onMouseMove(x, y)) {
			process();
		}
	}

	void update(void) {

	}

	void render(void) {
		SDL_Rect rect = {WINDOW_WIDTH / 5, WINDOW_HEIGHT / 5, WINDOW_WIDTH / 5 * 3, WINDOW_HEIGHT / 5 * 3};
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xEF);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderCopy(renderer, notice.getTexture(), nullptr, notice.getRect());
		SDL_RenderCopy(renderer, current == 0 ? yesBtn.getActive() : yesBtn.getNormal(), nullptr, yesBtn.getRect());
		SDL_RenderCopy(renderer, current == 1 ? noBtn.getActive() : noBtn.getNormal(), nullptr, noBtn.getRect());
	}
};

class Dialogue: public Scene {
private:
	Script script;
	Texture background, character, text, name, delta;
	int tick = 0;
public:
	Dialogue(void) {
		script = Script("begin.scr");
		background = script.getBackground();
		character = script.getCharacter();
		text = Texture(WINDOW_WIDTH * 12 / 100 , WINDOW_HEIGHT * 72 / 100,
			resources.text(script.getText(), resources.font("BIZ-UDMinchoM.ttc", 24))
		);
		name = Texture(WINDOW_WIDTH * 12 / 100, WINDOW_HEIGHT * 68 / 100,
			resources.text(script.getCharacterName(), resources.font("Coda.ttf", 24))
		);
		delta = Texture(WINDOW_WIDTH * 85 / 100 , WINDOW_HEIGHT * 85 / 100,
			resources.text("▼", resources.font("BIZ-UDMinchoM.ttc", 24))
		);
	}

	void update(void) {
		// Enter -> Next: Script.next
		// Else: Animation
		tick++;
		if (tick < 10) {
			delta.move(0, 1);
		} else if (tick < 20) {
			delta.move(0, -1);
		} else {
			tick = -1;
		}
	}

	void render(void) {
		SDL_RenderCopy(renderer, background.getTexture(), nullptr, background.getRect());
		SDL_RenderCopy(renderer, character.getTexture(), nullptr, character.getRect());
		SDL_Rect rect = {WINDOW_WIDTH * 10 / 100, WINDOW_HEIGHT * 70 / 100, WINDOW_WIDTH * 80 / 100, WINDOW_HEIGHT * 20 / 100};
		SDL_SetRenderDrawColor(renderer, 0, 128, 192, 0xEF);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_RenderFillRect(renderer, &rect);
		SDL_Rect rect2 = {WINDOW_WIDTH * 11 / 100, WINDOW_HEIGHT * 67 / 100, WINDOW_WIDTH * 5 / 100, WINDOW_HEIGHT * 5 / 100};
		SDL_SetRenderDrawColor(renderer, 255, 201, 14, 0xBF);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_RenderFillRect(renderer, &rect2);
		SDL_RenderCopy(renderer, text.getTexture(), nullptr, text.getRect());
		SDL_RenderCopy(renderer, name.getTexture(), nullptr, name.getRect());
		SDL_RenderCopy(renderer, delta.getTexture(), nullptr, delta.getRect());
	}
};

class Start: public Scene {
private:
	int current = 3; 
	// 0: Game Start
	// 1: Continue
	// 2: Exit
	Texture text;
	Button startBtn, continueBtn, exitBtn;

public:
	Start(void) {
		startBtn = Button(100, 200,
			resources.text(" Game Start ", resources.font("Coda.ttf", 60)),
			resources.text("<Game Start>", resources.font("Coda.ttf", 60))
		);
		
		continueBtn = Button(450, 250,
			resources.text(" Continue ", resources.font("Coda.ttf", 60)),
			resources.text("<Continue>", resources.font("Coda.ttf", 60))
		);
		
		exitBtn = Button(800, 300,
			resources.text(" Exit ", resources.font("Coda.ttf", 60)),
			resources.text("<Exit>", resources.font("Coda.ttf", 60))
		);
		
		text = Texture(560, 100, resources.text("Nula Lilio", resources.font("Deng.ttf", 100)));
	}

	void process(void) {
		if (current == 0) {
			scenes.jump(new Dialogue);
		} else if (current == 1) {
			scenes.jump(new Load);
		} else if (current == 2) {
			scenes.push(new Exit);
		}
		current = 3;
	}

	void onKeyDown(SDL_Keycode code) {
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

	bool onMouseMove(int x, int y) {
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

	void onMouseDown(int x, int y) {
		if (onMouseMove(x, y)) {
			process();
		}
	}

	void update(void) {

	}

	void render(void) {
		// int w, h;
		// SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
		SDL_RenderCopy(renderer, resources.picture("photo.jpg"), nullptr, nullptr);
		SDL_RenderCopy(renderer, text.getTexture(), nullptr, text.getRect());
		SDL_RenderCopy(renderer, current == 0 ? startBtn.getActive() : startBtn.getNormal(), nullptr, startBtn.getRect());
		SDL_RenderCopy(renderer, current == 1 ? continueBtn.getActive() : continueBtn.getNormal(), nullptr, continueBtn.getRect());
		SDL_RenderCopy(renderer, current == 2 ? exitBtn.getActive() : exitBtn.getNormal(), nullptr, exitBtn.getRect());
		
		// SDL_Rect rect = {x, y, w, h};
		// SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		// SDL_RenderFillRect(renderer, &rect);
		// SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
		// SDL_RenderDrawRect(renderer, &rect);
		// SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x3F);
		// SDL_RenderDrawLine(renderer, x, y, x + 20, y + 10);
		// SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0x3F);
		// SDL_RenderDrawPoint(renderer, x + 30, y + 30);
		// SDL_RenderCopy(renderer, resources.picture("photo.bmp"), nullptr, &rect);
		// SDL_RenderCopy(renderer, text, nullptr, &rect);
	}
};

class Engine {
public:
	bool init(void) {
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

		scenes.push(new Start);

		return true;
	}

	void close(void) {
		resources.free();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	void run(void) {
		running = true;
		SDL_Event e;
		while (running) {
			SDL_RenderClear(renderer);
			scenes.initFrame();
			while (SDL_PollEvent(&e)) {
				scenes.handle(e);
			}
			scenes.update();
			scenes.render();
			SDL_RenderPresent(renderer);
			SDL_Delay(1000 / 60);
		}
	}
};

int main(int argc, char *args[]) {
	Engine game;
	game.init();
	game.run();
	game.close();
	return 0;
}
