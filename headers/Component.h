#pragma once

#include <string>

class Component;

#include "GameObject.h"

class Component {
public:
    Component(GameObject& gameObject) : mGameObject{gameObject} {}

    virtual void Update(float dt) = 0;

    virtual void Render() = 0;

    virtual bool Is(std::string type) = 0;

    virtual ~Component() {}

    GameObject& mGameObject;
};
