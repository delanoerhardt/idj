#pragma once

#include <memory>
#include <vector>

#include "GameObject.h"
#include "components/Sprite.h"
#include "resources/Music.h"

typedef std::vector<std::shared_ptr<GameObject>> t_objects;

class State {
public:
    State();

    bool QuitRequested();

    void LoadAssets();

    void Start();

    void Update(float dt);

    void Render();

    std::weak_ptr<GameObject> AddObject(GameObject *gameObject);

    std::weak_ptr<GameObject> GetObject(GameObject *gameObject);

    ~State();

private:
    void CheckCollisions();

    t_objects mObjects;

    Music mMusic;

    bool mStarted = false;

    bool mQuitRequested = false;
};
