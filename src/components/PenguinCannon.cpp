#include "components/PenguinCannon.h"

#include "Camera.h"
#include "Game.h"
#include "components/Bullet.h"
#include "components/Collider.h"
#include "resources/InputManager.h"

#define CANNON_COOLDOWN 0.5

PenguinCannon::PenguinCannon(GameObject& gameObject,
                             std::weak_ptr<GameObject> penguinBody)
    : Component{gameObject}, mPenguinBody{penguinBody} {
    if (mPenguinBody.expired()) {
        mGameObject.RequestDelete();
        return;
    }

    Sprite* sprite = new Sprite(gameObject, "assets/img/cubngun.png");

    sprite->SetScale(0.7, 0.7);

    mGameObject.AddComponent(sprite);

    Collider* collider = new Collider(gameObject);

    mGameObject.AddComponent(collider);
}

void PenguinCannon::Update(float dt) {
    mCannonCooldown.Update(dt);

    auto penguinBodyPtr = mPenguinBody.lock();

    if (!penguinBodyPtr) {
        mGameObject.RequestDelete();
        return;
    }

    Vec2 gameObjectCenterBox = penguinBodyPtr->mBox.Center();

    mGameObject.mBox.SetCenterTo(gameObjectCenterBox);

    mAngle = (InputManager::GetMousePos() + Camera::sPos)
                 .AngleBetween(gameObjectCenterBox);

    mGameObject.mAngle = mAngle;

    if (InputManager::ButtonPressed(SDL_BUTTON_LEFT)) {
        Shoot();
    }
}

void PenguinCannon::Shoot() {
    if (mCannonCooldown.Get() < CANNON_COOLDOWN) {
        return;
    }

    GameObject* bulletObject = new GameObject();

    Bullet* bulletComponent =
        new Bullet(*bulletObject, mAngle, 700, 10, 200 * 50,
                   "assets/img/minionbullet2.png", 3, 0.1);
    bulletComponent->mTargetsPlayer = false;

    bulletObject->CenterAt(mGameObject.mBox.Center());

    bulletObject->AddComponent(bulletComponent);

    Game::GetCurrentState().AddObject(bulletObject);

    mCannonCooldown.Restart();
}
