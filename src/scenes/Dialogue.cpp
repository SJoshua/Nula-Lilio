#include "scenes/Dialogue.h"

extern Audio audio;
extern SceneManager scenes;
extern ResourceManager resources;
extern SDL_Renderer *renderer;
extern SDL_Window *window;

Dialogue::Dialogue(std::string filename, int pos) {
	script = Script(filename, pos);
	processScript();
	delta = Texture(WINDOW_WIDTH * 85 / 100, WINDOW_HEIGHT * 84 / 100,
		resources.text("▼", resources.font(DEFAULT_FONT, 24)));
	autoBtn = Button(WINDOW_WIDTH / 100 * 47, WINDOW_HEIGHT / 100 * 94,
		resources.text(" Auto ", resources.font(DEFAULT_FONT, 40)),
		resources.text("[Auto]", resources.font(DEFAULT_FONT, 40)));
	skipBtn = Button(WINDOW_WIDTH / 100 * 56, WINDOW_HEIGHT / 100 * 94,
		resources.text(" Skip ", resources.font(DEFAULT_FONT, 40)),
		resources.text("[Skip]", resources.font(DEFAULT_FONT, 40)));
	saveBtn = Button(WINDOW_WIDTH / 100 * 65, WINDOW_HEIGHT / 100 * 94,
		resources.text(" Save ", resources.font(DEFAULT_FONT, 40)),
		resources.text("[Save]", resources.font(DEFAULT_FONT, 40)));
	loadBtn = Button(WINDOW_WIDTH / 100 * 74, WINDOW_HEIGHT / 100 * 94,
		resources.text(" Load ", resources.font(DEFAULT_FONT, 40)),
		resources.text("[Load]", resources.font(DEFAULT_FONT, 40)));
	titleBtn = Button(WINDOW_WIDTH / 100 * 83, WINDOW_HEIGHT / 100 * 94,
		resources.text(" Title ", resources.font(DEFAULT_FONT, 40)),
		resources.text("[Title]", resources.font(DEFAULT_FONT, 40)));
}

SDL_Texture *Dialogue::takeScreenshot(void) {
	SDL_Texture *screenshot = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_Texture *ret = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	SDL_SetRenderTarget(renderer, screenshot);
	render();

	SDL_SetRenderTarget(renderer, ret);
	SDL_Rect rect = { 0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
	SDL_RenderCopy(renderer, screenshot, nullptr, &rect);

	SDL_SetRenderTarget(renderer, nullptr);

	return ret;
}

void Dialogue::processScript(void) {
	if (!script.next()) {
		scenes.jump(new Start);
		return;
	}
	lastTick = tick;
	bgPos = script.getBackgroundPosition();
	chPos = script.getCharacterPosition();
	background = Texture(bgPos.begin()->x, bgPos.begin()->y, resources.picture(script.getBackground()));
	if (!script.getCharacter().empty()) {
		showCharacter = true;
		character = Texture(chPos.begin()->x, chPos.begin()->y, resources.picture(script.getCharacter()));
	} else {
		showCharacter = false;
	}
	text = Texture(WINDOW_WIDTH * 12 / 100, WINDOW_HEIGHT * 72 / 100,
		resources.text(script.getText(), resources.font(DEFAULT_FONT, 24)));
	if (!script.getCharacterName().empty()) {
		showName = true;
		name = Texture(WINDOW_WIDTH * 12 / 100, WINDOW_HEIGHT * 64 / 100,
			resources.text(script.getCharacterName(), resources.font(DEFAULT_FONT, 24)));
	} else {
		showName = false;
	}
	auto list = script.getSelect();

	if (!list.empty()) {
		// Disable auto / skip mode.
		speed = 0;
		std::vector <Texture> selectTexts(list.size());
		int maxWidth = 0, maxHeight = 0;
		for (unsigned int i = 0; i < list.size(); i++) {
			selectTexts[i] = Texture(0, 0, resources.text(list[i].first, resources.font(DEFAULT_FONT, 30)));
			maxWidth = std::max(maxWidth, selectTexts[i].getRect()->w);
			maxHeight = std::max(maxHeight, selectTexts[i].getRect()->h);
		}
		int blockWidth = std::max(maxWidth + 5, WINDOW_WIDTH * 30 / 100);
		int blockHeight = maxHeight + 10;
		int gap = 30;
		int bottom = WINDOW_HEIGHT * 80 / 100;
		int totalHeight = blockHeight * list.size() + gap * (list.size() - 1);
		int top = (bottom - totalHeight) / 2;
		int left = (WINDOW_WIDTH - blockWidth) / 2;

		for (unsigned int i = 0; i < list.size(); i++) {
			auto normal = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, blockWidth, blockHeight);
			auto active = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, blockWidth, blockHeight);

			SDL_Rect rect = {
				(blockWidth - selectTexts[i].getRect()->w) / 2, (blockHeight - selectTexts[i].getRect()->h) / 2,
				selectTexts[i].getRect()->w, selectTexts[i].getRect()->h
			};

			SDL_SetRenderTarget(renderer, normal);
			SDL_SetTextureBlendMode(normal, SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(normal, 0x9F);
			SDL_SetRenderDrawColor(renderer, 0x4F, 0xFF, 0xFF, 0xFF);
			SDL_RenderFillRect(renderer, nullptr);
			SDL_RenderCopy(renderer, selectTexts[i].getTexture(), nullptr, &rect);

			SDL_SetRenderTarget(renderer, active);
			SDL_SetTextureBlendMode(active, SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(active, 0x9F);
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x9F, 0xEF, 0xFF);
			SDL_RenderFillRect(renderer, nullptr);
			SDL_RenderCopy(renderer, selectTexts[i].getTexture(), nullptr, &rect);

			select.push_back(std::make_pair(
				Button(left, top + i * (blockHeight + gap), normal, active),
				list[i].second));
		}
		SDL_SetRenderTarget(renderer, nullptr);
	} else {
		select.clear();
	}
	auto voice = script.getVoice();
	if (!voice.empty()) {
		audio.stopSound();
		audio.playSound(resources.chunk(voice));
	}
	if (bgm != script.getBGM()) {
		bgm = script.getBGM();
		audio.playMusic(resources.music(bgm));
	}
}

void Dialogue::onKeyDown(SDL_Keycode code) {
	switch (code) {
		case SDLK_RETURN:
		case SDLK_SPACE:
			//se.PlayChunk("test.wav");
			if (select.empty()) {
				processScript();
			}
			break;
	}
}

void Dialogue::processButtons(void) {
	if (current == 0) {
		// switch auto mode
		if (!select.empty()) {
			return;
		}
		if (speed == 100) {
			speed = 0;
		} else {
			speed = 100;
		}
	} else if (current == 1) {
		// switch skip mode
		if (!select.empty()) {
			return;
		}
		if (speed == 2) {
			speed = 0;
		} else {
			speed = 2;
		}
	} else if (current == 2) {
		scenes.push(new Save(Savedata(
			script.getTag(),
			script.getText(),
			script.getPosition(),
			takeScreenshot(),
			time(nullptr))));
	} else if (current == 3) {
		scenes.push(new Load);
	} else if (current == 4) {
		scenes.jump(new Start);
	} else if (current >= 10) {
		script.jump(select[current - 10].second);
		processScript();
	}
	current = 5;
}

bool Dialogue::onMouseMove(int x, int y) {
	if (autoBtn.isInside(x, y)) {
		current = 0;
		return true;
	} else if (skipBtn.isInside(x, y)) {
		current = 1;
		return true;
	} else if (saveBtn.isInside(x, y)) {
		current = 2;
		return true;
	} else if (loadBtn.isInside(x, y)) {
		current = 3;
		return true;
	} else if (titleBtn.isInside(x, y)) {
		current = 4;
		return true;
	} else if (!select.empty()) {
		for (unsigned int i = 0; i < select.size(); i++) {
			if (select[i].first.isInside(x, y)) {
				current = i + 10;
				return true;
			}
		}
		current = 5;
		return true;
	} else {
		current = 5;
	}
	return false;
}

void Dialogue::onMouseDown(int x, int y) {
	if (onMouseMove(x, y)) {
		processButtons();
	} else {
		if (speed > 0) {
			speed = 0;
		} else {
			processScript();
		}
	}
}

void Dialogue::update(void) {
	tick++;
	if (tick % 20 < 10) {
		delta.move(0, 1);
	} else if (tick % 20 < 20) {
		delta.move(0, -1);
	}
	if (speed) {
		if (tick % speed == 0) {
			processScript();
		}
	}
	if (bgPos.size() > 1) {
		// speed: the number of ticks required for one step
		int dur = tick - lastTick;
		int spd = script.getBackgroundSpeed();
		if (!spd) {
			spd = 30;
		}
		unsigned int step = dur / spd;
		int delt = dur % spd;
		if (step < bgPos.size() - 1) {
			int x_step = bgPos[step + 1].x - bgPos[step].x;
			int y_step = bgPos[step + 1].y - bgPos[step].y;
			background.moveTo(bgPos[step].x + x_step * delt / spd, bgPos[step].y +  y_step * delt / spd);
		} else {
			background.moveTo(bgPos.back().x, bgPos.back().y);
		}
	}
	
}

void Dialogue::render(void) {
	// Background
	SDL_RenderCopy(renderer, background.getTexture(), nullptr, background.getRect());

	// Character
	if (showCharacter) {
		SDL_RenderCopy(renderer, character.getTexture(), nullptr, character.getRect());
	}

	// Text Box
	SDL_Rect rect = { WINDOW_WIDTH * 10 / 100, WINDOW_HEIGHT * 70 / 100, WINDOW_WIDTH * 80 / 100, WINDOW_HEIGHT * 20 / 100 };
	SDL_SetRenderDrawColor(renderer, 180, 193, 250, 0xCF);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &rect);

	// Name
	if (showName) {
		SDL_Rect rect2 = { WINDOW_WIDTH * 11 / 100, WINDOW_HEIGHT * 63 / 100, WINDOW_WIDTH * 12 / 100, WINDOW_HEIGHT * 6 / 100 };
		SDL_SetRenderDrawColor(renderer, 255, 201, 14, 0xBF);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_RenderFillRect(renderer, &rect2);
		auto nameRect = *name.getRect();
		nameRect.x = rect2.x + (rect2.w - nameRect.w) / 2;
		nameRect.y = rect2.y + (rect2.h - nameRect.h) / 2;
		SDL_RenderCopy(renderer, name.getTexture(), nullptr, &nameRect);
	}
	SDL_RenderCopy(renderer, text.getTexture(), nullptr, text.getRect());

	// Indicator
	SDL_RenderCopy(renderer, delta.getTexture(), nullptr, delta.getRect());

	// Toolbar
	SDL_Rect rect3 = { WINDOW_WIDTH * 44 / 100, WINDOW_HEIGHT * 93 / 100, WINDOW_WIDTH * 46 / 100, WINDOW_HEIGHT * 65 / 1000 };
	SDL_SetRenderDrawColor(renderer, 255, 174, 201, 0x5F);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &rect3);

	// Button
	SDL_RenderCopy(renderer, (current == 0 || speed == 100) ? autoBtn.getActive() : autoBtn.getNormal(), nullptr, autoBtn.getRect());
	SDL_RenderCopy(renderer, (current == 1 || speed == 2) ? skipBtn.getActive() : skipBtn.getNormal(), nullptr, skipBtn.getRect());
	SDL_RenderCopy(renderer, current == 2 ? saveBtn.getActive() : saveBtn.getNormal(), nullptr, saveBtn.getRect());
	SDL_RenderCopy(renderer, current == 3 ? loadBtn.getActive() : loadBtn.getNormal(), nullptr, loadBtn.getRect());
	SDL_RenderCopy(renderer, current == 4 ? titleBtn.getActive() : titleBtn.getNormal(), nullptr, titleBtn.getRect());

	// Select
	for (unsigned int i = 0; i < select.size(); i++) {
		SDL_RenderCopy(renderer, current == i + 10 ? select[i].first.getActive() : select[i].first.getNormal(), nullptr, select[i].first.getRect());
	}
}
