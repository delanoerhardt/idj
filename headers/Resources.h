#pragma once

#include <string>
#include <unordered_map>

#include "Game.h"
#include "Texture.h"

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Resources {
public:
    static Texture& GetImage(std::string file);
    static void ClearImages();
    static Mix_Music* GetMusic(std::string file);
    static void ClearMusics();
    static Mix_Chunk* GetSound(std::string file);
    static void ClearSounds();

private:
    static std::unordered_map<std::string, Texture> imageTable;
    static std::unordered_map<std::string, Mix_Music*> musicTable;
    static std::unordered_map<std::string, Mix_Chunk*> soundTable;
};