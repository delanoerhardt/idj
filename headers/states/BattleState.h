#pragma once

#include "State.h"

class BattleState : public State {
public:
    BattleState();

    virtual void Update(float dt);

    virtual void Resume();
};