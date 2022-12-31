#pragma once

#include <memory>
#include <vector>

#include "GameObject.h"
#include "State.h"
#include "components/Sprite.h"
#include "resources/Music.h"
#include "util/Logger.h"

class StageState : public State {
public:
    StageState();

    virtual void Update(float dt);

    virtual void Pause();

    virtual ~StageState() {}

private:
    void CheckCollisions();

    Music mMusic;

    std::shared_ptr<GameObject> mPenguinPtr;
};
