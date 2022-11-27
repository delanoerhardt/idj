#pragma once

#include <string>

#include "Component.h"

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Sound : public Component {
public:
    Sound(GameObject &gameObject);

    Sound(GameObject &gameObject, std::string file);

    void Play(int loops = 0);

    void Stop();

    void Open(std::string file);

    bool IsOpen();

    virtual void Update(float dt);

    virtual void Render();

    virtual bool Is(std::string type);

    virtual ~Sound();

private:
    Mix_Chunk *mChunk;
    int mChannel;
};
