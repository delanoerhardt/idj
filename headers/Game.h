#pragma once

#include <memory>
#include <stack>
#include <string>

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include "states/State.h"
#include "util/Logger.h"

class Game {
public:
    static Game &GetInstance();

    static SDL_Renderer *GetRenderer() { return GetInstance().mRenderer; }
    static State &GetCurrentState() { return *GetInstance().mStateStack.top(); }

    static void Push(State *state) { GetInstance().mStoredState = state; }

    void Run();

    ~Game();

    float mDeltaTime;

private:
    Game(std::string title, u_int32_t width, u_int32_t height);

    void PushStored() {
        if (mStoredState == nullptr) {
            return;
        }

        if (!mStateStack.empty()) {
            mStateStack.top()->Pause();
        }

        mStateStack.emplace(mStoredState);
        mStateStack.top()->Start();

        mStoredState = nullptr;
    }

    static Game *sInstance;

    uint32_t mFrameStart;

    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;

    State *mStoredState;
    std::stack<std::unique_ptr<State>> mStateStack;
};