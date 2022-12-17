#pragma once

#include <memory>
#include <queue>

#include "Component.h"
#include "Sprite.h"

class Alien : public Component {
public:
    Alien(GameObject& gameObject, int minionAmount);

    virtual void Start();

    virtual void Update(float dt);

    virtual bool Is(std::string type) { return type == "Alien"; }

private:
    class Action;

    Vec2 mSpeed;
    int mHp;

    int mMinionAmount;

    Sprite* mSprite;

    std::queue<Alien::Action> mTaskQueue;
    std::vector<std::weak_ptr<GameObject>> mMinionArray;
};

class Alien::Action {
public:
    enum Type { MOVE, SHOOT };

    Action(Type type, float x, float y) : mType{type}, mPos{x, y} {}

    Action(Type type, int x, int y) : mType{type}, mPos{x, y} {}

    Action(Type type, Vec2 pos) : mType{type}, mPos{pos} {}

    Type mType;

    Vec2 mPos;
};
