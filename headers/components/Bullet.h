#pragma once

#include "Component.h"

class Bullet : public Component {
public:
    Bullet(GameObject& gameObject, float angle, float speed, int damage,
           float maxDistance, std::string spriteFilePath, float frameCount = 1,
           float frameTime = 1);

    Bullet(GameObject& gameObject, Vec2 destination, float speed, int damage,
           float maxDistance, std::string spriteFilePath, float frameCount = 1,
           float frameTime = 1);

    virtual void Update(float dt);

    virtual bool Is(std::string type) { return type == "Bullet"; };

    int mDamage;

private:
    Vec2 mSpeed;

    float mDistanceLeft;
};
