#pragma once

#include "State.h"

class TitleState : public State {
public:
    TitleState();

    virtual void Update(float dt);

    virtual void Resume();

    virtual ~TitleState() {}
};