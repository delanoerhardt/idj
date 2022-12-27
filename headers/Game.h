#pragma once

#include <string>
#include <cstdint>

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include "State.h"

class Game {
public:
    static Game &GetInstance();

    SDL_Renderer *GetRenderer();

    State &GetState();

    void Run();

    ~Game();

    float mDeltaTime;

private:
    Game(std::string title, uint32_t width, uint32_t height);

    static Game *sInstance;

    uint32_t mFrameStart;

    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    State *mState;
};