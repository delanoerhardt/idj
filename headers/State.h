#pragma once

#include <memory>
#include <vector>

#include "GameObject.h"
#include "components/Sprite.h"
#include "resources/Music.h"

typedef std::vector<std::unique_ptr<GameObject>> t_objects;

class State {
public:
    State();

    bool QuitRequested();

    void LoadAssets();

    void Update(float dt);

    void Render();

    void AddObject(int x, int y);

    ~State();

private:
    t_objects mObjects;
    Music mMusic;
    bool mQuitRequested;
};
