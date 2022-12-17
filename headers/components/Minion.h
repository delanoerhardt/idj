#pragma once

#include <memory>

#include "Component.h"
#include "Sprite.h"

class Minion : public Component {
public:
    Minion(GameObject& gameObject, GameObject& alienObject,
           float arcOffsetDeg = 0);

    void Shoot(Vec2 target);

    virtual void Update(float dt);

    virtual bool Is(std::string type) { return type == "Minion"; }

private:
    GameObject& mAlienObject;
    float mAngle;

    Sprite* mSprite;
};