#pragma once

#include "Music.h"
#include "Sprite.h"

class State {
public:
    State();

    bool QuitRequested();

    void LoadAssets();

    void Update(float dt);

    void Render();

private:
    Sprite mBackgroundSprite;
    Music mMusic;
    bool mQuitRequested;
};