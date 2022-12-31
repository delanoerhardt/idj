#include "resources/Resources.h"

std::unordered_map<std::string, Texture> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;
std::unordered_map<std::string, TTF_Font*> Resources::fontTable;

Texture& Resources::GetImage(std::string file) {
    auto it = imageTable.find(file);

    if (it != imageTable.end()) {
        return it->second;
    }

    Texture texture;

    texture.sdlTexture =
        IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    if (texture.sdlTexture == NULL) {
        printf("Failed to open Image %s due to %s\n", file.c_str(),
               SDL_GetError());
        exit(1);
    }

    int errorValue = SDL_QueryTexture(texture.sdlTexture, nullptr, nullptr,
                                      &texture.width, &texture.height);

    if (errorValue != 0) {
        printf("Failed to query texture due to %s\n", SDL_GetError());
    }

    Texture& textureRef = imageTable[file];

    textureRef = texture;

    return textureRef;
}

void Resources::ClearImages() {
    for (auto&& image : imageTable) {
        SDL_DestroyTexture(image.second.sdlTexture);
    }

    imageTable.clear();
}

Mix_Music* Resources::GetMusic(std::string file) {
    auto it = musicTable.find(file);

    if (it != musicTable.end()) {
        return it->second;
    }

    Mix_Music* music = Mix_LoadMUS(file.c_str());

    if (music == nullptr) {
        printf("Failed to open Music %s due to %s\n", file.c_str(),
               SDL_GetError());

        exit(1);
    }

    musicTable[file] = music;

    return music;
}

void Resources::ClearMusics() {
    for (auto&& music : musicTable) {
        Mix_FreeMusic(music.second);
    }

    musicTable.clear();
}

Mix_Chunk* Resources::GetSound(std::string file) {
    auto it = soundTable.find(file);

    if (it != soundTable.end()) {
        return it->second;
    }

    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());

    if (chunk == nullptr) {
        printf("Failed to open Sound %s due to %s\n", file.c_str(),
               SDL_GetError());

        exit(1);
    }

    soundTable[file] = chunk;

    return chunk;
}

void Resources::ClearSounds() {
    for (auto&& sound : soundTable) {
        Mix_FreeChunk(sound.second);
    }

    soundTable.clear();
}

TTF_Font* Resources::GetFont(std::string file, int ptSize) {
    std::string uniqueFontName = file + std::to_string(ptSize);
    auto it = fontTable.find(uniqueFontName);

    if (it != fontTable.end()) {
        return it->second;
    }

    TTF_Font* font = TTF_OpenFont(file.c_str(), ptSize);

    if (font == nullptr) {
        printf("Failed to open font %s due to %s\n", uniqueFontName.c_str(),
               TTF_GetError());

        exit(1);
    }

    return fontTable[uniqueFontName] = font;
}

void Resources::ClearFonts() {
    for (auto&& font : fontTable) {
        TTF_CloseFont(font.second);
    }

    fontTable.clear();
}
