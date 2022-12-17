#pragma once

#include <string>
#include <vector>

class GameObject;

#include "components/Component.h"
#include "util/Rect.h"

class GameObject {
public:
    GameObject() {}

    GameObject(float x, float y) : mBox{x, y, 0.0, 0.0} {}

    GameObject(Rect r) : mBox{r.x, r.y, 0.0, 0.0} {}

    GameObject(Vec2 v) : mBox{v.x, v.y, 0.0, 0.0} {}

    void Start();

    void Update(float dt);

    void Render();

    bool IsDead();

    void RequestDelete();

    void AddComponent(Component* cpt);

    void RemoveComponent(Component* cpt);

    Component* GetComponent(std::string type);

    ~GameObject();

    Rect mBox;

private:
    std::vector<Component*> mComponents;

    bool mIsDead = false;
    bool mStarted = false;
};
