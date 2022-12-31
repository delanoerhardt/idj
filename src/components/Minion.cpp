#include "components/Minion.h"

#include "Game.h"
#include "components/Bullet.h"
#include "components/Collider.h"

#define ANGULAR_SPEED M_PI / 2

#define BULLET_SPEED 200

#define CENTER_DISTANCE 160

Minion::Minion(GameObject& gameObject, std::weak_ptr<GameObject> alienObject,
               float angle)
    : Component{gameObject}, mAlienObject{alienObject}, mAngle{angle} {
    auto alienPtr = mAlienObject.lock();

    if (!alienPtr) {
        mGameObject.RequestDelete();
        return;
    }

    Sprite* sprite = new Sprite(gameObject, "assets/img/minion.png");

    float scale = 1 + (rand() % 10) / 20.0;
    sprite->SetScale(scale, scale);

    gameObject.AddComponent(sprite);

    Collider* collider = new Collider(gameObject);

    mGameObject.AddComponent(collider);

    mGameObject.mBox.SetCenterTo(alienPtr->mBox.Center() +
                                 Vec2{CENTER_DISTANCE, 0}.Rotate(mAngle));
}

void Minion::Update(float dt) {
    auto alienPtr = mAlienObject.lock();

    if (!alienPtr) {
        mGameObject.RequestDelete();
        return;
    }

    mAngle += dt * ANGULAR_SPEED;

    mGameObject.mAngle = mAngle + M_PI / 2;

    mGameObject.mBox.SetCenterTo(alienPtr->mBox.Center() +
                                 Vec2{CENTER_DISTANCE, 0}.Rotate(mAngle));
}

void Minion::Shoot(Vec2 target) {
    GameObject* bulletObject = new GameObject(mGameObject.mBox.Center());

    Bullet* bulletComponent =
        new Bullet(*bulletObject, target, BULLET_SPEED, 10, BULLET_SPEED * 50,
                   "assets/img/minionbullet2.png", 3, 0.1);
    bulletComponent->mTargetsPlayer = true;

    bulletObject->AddComponent(bulletComponent);

    Game::GetCurrentState().AddObject(bulletObject);
}
