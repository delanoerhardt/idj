#pragma once

#include <string>

#include "Component.h"

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Sound : public Component {
public:
    Sound(GameObject &gameObject);

    Sound(GameObject &gameObject, const char *file);

    void Play(int times = 0);

    void Stop();

    void Open(const char *file);

    bool IsOpen();

    virtual void Update(float dt);

    virtual void Render();

    virtual bool Is(std::string type);

    virtual ~Sound();

    static Mix_Chunk *sChunkPlayingInChannel[];

    static void FreeAlreadyPlayed(int channel);

private:
    Mix_Chunk *mChunk;
    int mChannel;
};
