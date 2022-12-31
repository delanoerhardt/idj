#pragma once

#include "State.h"
#include "resources/Music.h"

class EndState : public State {
public:
    EndState();

    virtual void Update(float dt);

    virtual void Resume();

    virtual ~EndState() { delete mMusic; }

private:
    Music *mMusic;
};
