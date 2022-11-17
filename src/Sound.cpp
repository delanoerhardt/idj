#include "Sound.h"

#include "Constants.h"

Mix_Chunk *Sound::sChunkPlayingInChannel[CHANNELS_AMOUNT];

Sound::Sound(GameObject &gameObject)
    : Component{gameObject}, mChunk{nullptr}, mChannel{-1} {}

Sound::Sound(GameObject &gameObject, const char *file) : Sound(gameObject) {
    Open(file);
}

void Sound::Open(const char *file) {
    mChunk = Mix_LoadWAV(file);

    if (mChunk == nullptr) {
        printf("Failed to open Sound %s due to %s\n", file, SDL_GetError());

        exit(1);
    }

    Mix_VolumeChunk(mChunk, 32);
}

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

void Sound::FreeAlreadyPlayed(int channel) {
    if (sChunkPlayingInChannel[channel] == nullptr) {
        return;
    }

    Mix_Chunk *chunk = sChunkPlayingInChannel[channel];
    sChunkPlayingInChannel[channel] = nullptr;

    Mix_FreeChunk(chunk);
}

Sound::~Sound() {
    if (mChannel == -1 || mChunk == nullptr) {
        return;
    }

    sChunkPlayingInChannel[mChannel] = mChunk;

    Mix_ChannelFinished(Sound::FreeAlreadyPlayed);
}
