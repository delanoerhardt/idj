#pragma once

#include <memory>

#include "Component.h"
#include "Sprite.h"
#include "Timer.h"

class PenguinCannon : public Component {
public:
    PenguinCannon(GameObject& gameObject,
                  std::weak_ptr<GameObject> penguinBody);

    virtual void Update(float dt);

    virtual bool Is(std::string type) { return type == "PenguinCannon"; }

    void Shoot();

private:
    std::weak_ptr<GameObject> mPenguinBody;

    float mAngle;

    Timer mCannonCooldown;
};