#pragma once

#include <memory>
#include <vector>

#include "GameObject.h"
#include "util/Logger.h"

typedef std::vector<std::shared_ptr<GameObject>> t_objects;

class State {
public:
    State() {}

    virtual void LoadAssets() {}

    virtual void Update(float dt) = 0;
    virtual void Render();

    virtual void Start();
    virtual void Pause();
    virtual void Resume();

    bool PopRequested() { return mPopRequested; }
    bool QuitRequested() { return mQuitRequested; }

    std::weak_ptr<GameObject> AddObject(GameObject *gameObject);
    std::weak_ptr<GameObject> GetObject(GameObject *gameObject);

    virtual ~State() { mObjects.clear(); }

protected:
    virtual void StartArray();
    virtual void UpdateArray(float dt);
    virtual void UpdateDeadArray();
    virtual void RenderArray();

    t_objects mObjects;

    bool mPopRequested = false;
    bool mQuitRequested = false;
    bool mStarted = false;
};
