#include "components/Minion.h"

#include "Game.h"
#include "components/Bullet.h"

#define ANGULAR_SPEED M_PI / 2

#define BULLET_SPEED 200

#define CENTER_DISTANCE 160

Minion::Minion(GameObject& gameObject, GameObject& alienObject, float angle)
    : Component{gameObject}, mAlienObject{alienObject}, mAngle{angle} {
    mSprite = new Sprite(gameObject, "assets/img/minion.png");

    float scale = 1 + (rand() % 10) / 20.0;
    mSprite->SetScale(scale, scale);

    gameObject.AddComponent(mSprite);

    mGameObject.mBox.SetCenterTo(mAlienObject.mBox.Center() +
                                 Vec2{CENTER_DISTANCE, 0}.Rotate(mAngle));
}

void Minion::Update(float dt) {
    mAngle += dt * ANGULAR_SPEED;

    mSprite->mAngleDeg = (mAngle + M_PI / 2) * RAD2DEG;

    mGameObject.mBox.SetCenterTo(mAlienObject.mBox.Center() +
                                 Vec2{CENTER_DISTANCE, 0}.Rotate(mAngle));
}

void Minion::Shoot(Vec2 target) {
    GameObject* bulletObject = new GameObject(mGameObject.mBox.Center());

    Bullet* bulletComponent =
        new Bullet(*bulletObject, target, BULLET_SPEED, 10, BULLET_SPEED * 500,
                   "assets/img/minionbullet1.png");

    bulletObject->AddComponent(bulletComponent);

    Game::GetInstance().GetState().AddObject(bulletObject);
}
