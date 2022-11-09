#include "Music.h"

Music::Music() : mMusic{nullptr} {}

Music::Music(std::string file) : Music() { Open(file); }

void Music::Open(std::string file) {
    mMusic = Mix_LoadMUS(file.c_str());

    if (mMusic == nullptr) {
        printf("Failed to open Music %s due to %s\n", file.c_str(),
               SDL_GetError());

        printf("\n");

        exit(1);
    }
}

void Music::Play(int times) {
    if (mMusic == nullptr) {
        return;
    }

    Mix_PlayMusic(mMusic, times);
}

void Music::Stop(int msToStop) { Mix_FadeOutMusic(msToStop); }

bool Music::IsOpen() { return mMusic != nullptr; }

Music::~Music() { Mix_FreeMusic(mMusic); }
