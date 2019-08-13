#include "scenes/Load.h"

extern SceneManager scenes;
extern ResourceManager resources;
extern SDL_Renderer* renderer;

Load::Load(void) {
    data.resize(10);
    background = Texture(0, 0, resources.picture("grass.jpg"));
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

void Load::update(void) {
    
}

void Load::render(void) {
    // Background
    SDL_RenderCopy(renderer, background.getTexture(), nullptr, background.getRect());
    
    // Box
    SDL_Rect rect = {WINDOW_WIDTH * 5 / 100, WINDOW_HEIGHT * 5 / 100, WINDOW_WIDTH * 90 / 100, WINDOW_HEIGHT * 90 / 100};
    SDL_SetRenderDrawColor(renderer, 0, 128, 192, 0xEF);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(renderer, &rect);

    // Sub Box
    
    // Buttons
}
