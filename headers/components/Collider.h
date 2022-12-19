#pragma once

#include <memory>

#include "Component.h"

class Collider : public Component {
public:
    Collider(GameObject& gameObject, Vec2 scale = {1, 1}, Vec2 offset = {1, 1})
        : Component{gameObject}, mScale{scale}, mOffset{offset} {}

    virtual void Render();

    virtual void Update(float dt);

    virtual bool Is(std::string type) { return type == "Collider"; }

    void SetScale(Vec2 scale) { mScale = scale; }

    void SetOffset(Vec2 offset) { mOffset = offset; }

    Rect mBox;

private:
    Vec2 mScale;
    Vec2 mOffset;
};
