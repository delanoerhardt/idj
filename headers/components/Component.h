#pragma once

#include <string>

class Component;

#include "GameObject.h"

class Component {
public:
    Component(GameObject& gameObject) : mGameObject{gameObject} {}

    virtual void Start() {}

    virtual void Update(float dt) {}

    virtual void Render() {}

    virtual void NotifyCollision(GameObject& other) {}

    virtual bool Is(std::string type) = 0;

    virtual ~Component() {}

    GameObject& mGameObject;
};
