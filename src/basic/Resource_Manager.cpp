#include "Resource_Manager.h"

extern SDL_Renderer* renderer;

SDL_Texture* ResourceManager::loadPicture(std::string path) {
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

TTF_Font* ResourceManager::loadFont(std::string path, int size) {
    TTF_Font *font = TTF_OpenFont(path.c_str(), size);
    if (font == nullptr) {
        std::cout << TTF_GetError() << std::endl;
    } 
    return font;
}

ResourceManager::ResourceManager(void) {}

TTF_Font* ResourceManager::font(std::string filename, int size) {
    std::string path = "./resource/fonts/" + filename;
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

SDL_Texture* ResourceManager::picture(std::string filename) {
    std::string path = "./resource/pictures/" + filename;
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

SDL_Texture* ResourceManager::text(std::string text, TTF_Font *font, SDL_Color color) {
    auto *surface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), color, WINDOW_WIDTH);
    if (surface == nullptr) {
        std::cout << "[Failed] render text <" << text.c_str() << ">: " << TTF_GetError() << std::endl;
    }
    auto *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        std::cout << "[Failed] create texture: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(surface);
    return texture;
}

void ResourceManager::free(void) {
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
