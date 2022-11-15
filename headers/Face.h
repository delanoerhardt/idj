#pragma once

#include <string>

#include "Component.h"
#include "GameObject.h"

class Face : public Component {
public:
    Face(GameObject& gameObject);

    void Damage(int damage);

    virtual void Update(float dt);

    virtual void Render();

    virtual bool Is(std::string type);

    virtual ~Face() = default;

private:
    int mHitpoints;
};
