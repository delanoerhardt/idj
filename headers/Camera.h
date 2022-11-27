#pragma once

#include "GameObject.h"
#include "util/Vec2.h"

class Camera {
public:
    static void Follow(GameObject* newFocus);
    static void Unfollow();
    static void Update(float dt);
    static Vec2 sPos;
    static Vec2 sSpeed;

private:
    static GameObject* sFocus;
};
