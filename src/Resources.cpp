#include "Resources.h"

std::unordered_map<std::string, Texture> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

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

void Resources::ClearImages() { imageTable.clear(); }

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

void Resources::ClearMusics() { musicTable.clear(); }

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

void Resources::ClearSounds() { soundTable.clear(); }
