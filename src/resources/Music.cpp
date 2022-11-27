#include "resources/Music.h"

#include "resources/Resources.h"

Music::Music() : mMusic{nullptr} {}

Music::Music(std::string file) : Music() { Open(file); }

void Music::Open(std::string file) { mMusic = Resources::GetMusic(file); }

void Music::Play(int times) {
    if (mMusic == nullptr) {
        return;
    }

    Mix_PlayMusic(mMusic, times);
}

void Music::Stop(int msToStop) { Mix_FadeOutMusic(msToStop); }

bool Music::IsOpen() { return mMusic != nullptr; }

Music::~Music() { Mix_FreeMusic(mMusic); }
