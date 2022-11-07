#pragma once

#include <string>

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include "State.h"

class Game {
public:
    Game(std::string title, u_int32_t width, u_int32_t height);

    static Game &GetInstance();

    SDL_Renderer &GetRenderer();

    State &GetState();

    void Run();

    ~Game();

private:
    Game *mInstance;
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    State *mState;
};