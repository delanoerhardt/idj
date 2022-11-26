#include "Sound.h"

#include "Constants.h"
#include "Resources.h"

Sound::Sound(GameObject &gameObject)
    : Component{gameObject}, mChunk{nullptr}, mChannel{-1} {}

Sound::Sound(GameObject &gameObject, std::string file) : Sound(gameObject) {
    Open(file);
}

void Sound::Open(std::string file) { mChunk = Resources::GetSound(file); }

void Sound::Play(int loops) {
    if (mChunk == nullptr) {
        return;
    }

    mChannel = Mix_PlayChannel(-1, mChunk, loops);

    if (mChannel == -1) {
        printf("Failed to play Sound due to %s\n", SDL_GetError());
    }
}

void Sound::Stop() {
    if (mChunk == nullptr || mChannel == -1) {
        return;
    }

    Mix_HaltChannel(mChannel);
}

bool Sound::IsOpen() { return mChunk != nullptr; }

void Sound::Update(float dt) {}

void Sound::Render() {}

bool Sound::Is(std::string type) { return type == "Sound"; }

Sound::~Sound() {}
