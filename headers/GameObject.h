#pragma once

#include <string>
#include <vector>

class GameObject;

#include "components/Component.h"
#include "util/Rect.h"

class GameObject {
public:
    GameObject() : mIsDead{false} {}

    GameObject(float x, float y) : mBox{x, y, 0.0, 0.0}, mIsDead{false} {}

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
    bool mIsDead;
};
