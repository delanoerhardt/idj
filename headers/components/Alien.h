#pragma once

#include <memory>
#include <queue>

#include "Component.h"
#include "PenguinBody.h"
#include "Sprite.h"
#include "Timer.h"

class Alien : public Component {
public:
    Alien(GameObject& gameObject, int minionAmount);

    virtual void Start();

    virtual void Update(float dt);

    virtual void NotifyCollision(GameObject& other);

    virtual bool Is(std::string type) { return type == "Alien"; }

    static int alienCount;

    ~Alien() { alienCount--; }

private:
    void CreateExplosion();

    Vec2 mSpeed;
    int mHp;

    int mMinionAmount;

    std::vector<std::weak_ptr<GameObject>> mMinionArray;

    enum State { MOVING, RESTING };

    State mState;

    Timer mRestTimer;

    Vec2 mDestination;

    Vec2 GetPlayerPosition() {
        if (PenguinBody::sPlayer) {
            return PenguinBody::sPlayer->mGameObject.mBox.Center();
        }

        return mGameObject.mBox.Center();
    }
};
