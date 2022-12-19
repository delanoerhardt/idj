#pragma once

#include <memory>

#include "Component.h"
#include "Sprite.h"

class PenguinBody : public Component {
public:
    PenguinBody(GameObject& gameObject);

    ~PenguinBody();

    virtual void Start();

    virtual void Update(float dt);

    virtual void NotifyCollision(GameObject& other);

    virtual bool Is(std::string type) { return type == "PenguinBody"; }

    static PenguinBody* sPlayer;

    int mHp;

private:
    void CreateExplosion();

    std::weak_ptr<GameObject> mPenguinCannon;
    Vec2 mSpeed;
    float mLinearSpeed;
    float mAngle;
};
