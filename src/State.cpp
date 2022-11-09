#include "State.h"

State::State()
    : mQuitRequested(false),
      mBackgroundSprite{"assets/img/ocean.jpg"},
      mMusic{"assets/audio/stageState.ogg"} {
    mMusic.Play();
}

bool State::QuitRequested() { return mQuitRequested; }

void State::LoadAssets() {}

void State::Update(float dt) {
    if (SDL_QuitRequested()) {
        mQuitRequested = true;
    }
}

void State::Render() { mBackgroundSprite.Render(0, 0); }