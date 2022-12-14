#pragma once

#include <string>

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Music {
public:
    Music();

    Music(std::string file);

    void Play(int times = -1);

    void Stop(int msToStop = 1500);

    void Open(std::string file);

    bool IsOpen();

private:
    Mix_Music *mMusic;
};