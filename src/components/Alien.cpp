#include "components/Alien.h"

#include "Camera.h"
#include "Game.h"
#include "components/Minion.h"
#include "resources/InputManager.h"

#define ALIEN_SPEED 250
#define ALIEN_MIN_DISTANCE_TARGET 2

Alien::Alien(GameObject& gameObject, int minionAmount)
    : Component{gameObject}, mSpeed{}, mHp{30}, mMinionAmount{minionAmount} {
    mSprite = new Sprite{gameObject, "assets/img/alien.png"};

    gameObject.AddComponent(mSprite);
}

void Alien::Start() {
    auto alienPtr = Game::GetInstance().GetState().GetObject(&mGameObject);

    for (int i = 0; i < mMinionAmount; i++) {
        GameObject* minionObject = new GameObject();
        mMinionArray.push_back(
            Game::GetInstance().GetState().AddObject(minionObject));

        minionObject->AddComponent(
            new Minion(*minionObject, alienPtr, i * M_PI / 2));
    }
}

void Alien::Update(float dt) {
    mSprite->mAngleDeg -= 0.4;

    if (InputManager::ButtonPressed(SDL_BUTTON_LEFT)) {
        Vec2 actionPos = InputManager::GetMousePos() + Camera::sPos;
        Alien::Action action{Alien::Action::Type::SHOOT, actionPos};

        mTaskQueue.push(action);
    }

    if (InputManager::ButtonPressed(SDL_BUTTON_RIGHT)) {
        Vec2 actionPos = InputManager::GetMousePos() + Camera::sPos;
        Alien::Action action{Alien::Action::Type::MOVE, actionPos};

        mTaskQueue.push(action);
    }

    if (mTaskQueue.empty()) {
        return;
    }

    Alien::Action& action = mTaskQueue.front();

    if (action.mType == Alien::Action::Type::MOVE) {
        Vec2 movementDirection = action.mPos - mGameObject.mBox.Center();

        mGameObject.mBox += movementDirection.Normalized() * (ALIEN_SPEED * dt);

        Vec2 newMovementDirection = action.mPos - mGameObject.mBox.Center();

        if (movementDirection.DotProduct(newMovementDirection) <= 0) {
            mGameObject.mBox.SetCenterTo(action.mPos);
            mTaskQueue.pop();
        }
    } else if (action.mType == Alien::Action::Type::SHOOT &&
               mMinionArray.size() > 0) {
        auto l = mMinionArray[rand() % mMinionArray.size()].lock();

        if (l) {
            Minion* minion = (Minion*)l->GetComponent("Minion");
            minion->Shoot(action.mPos);
        }

        mTaskQueue.pop();
    }
}
