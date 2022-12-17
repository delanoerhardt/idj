#include "components/Bullet.h"

#include "components/Sprite.h"

Bullet::Bullet(GameObject& gameObject, float angle, float speed, int damage,
               float maxDistance, std::string spriteFilePath)
    : Component{gameObject}, mDamage{damage}, mDistanceLeft{maxDistance} {
    Sprite* sprite = new Sprite(gameObject, spriteFilePath);

    sprite->mAngleDeg = angle;

    gameObject.AddComponent(sprite);

    mSpeed = Vec2(1, 0).Rotate(angle) * speed;
}

Bullet::Bullet(GameObject& gameObject, Vec2 destination, float speed,
               int damage, float maxDistance, std::string spriteFilePath)
    : Component{gameObject}, mDamage{damage}, mDistanceLeft{maxDistance} {
    Sprite* sprite = new Sprite(gameObject, spriteFilePath);

    sprite->mAngleDeg =
        destination.AngleBetween(mGameObject.mBox.Center()) * RAD2DEG;

    gameObject.AddComponent(sprite);

    mSpeed = (destination - gameObject.mBox.Center()).Normalized() * speed;
}

void Bullet::Update(float dt) {
    mGameObject.mBox += mSpeed * dt;

    mDistanceLeft -= mSpeed.Length() * dt;
    if (mDistanceLeft < 0) {
        mGameObject.RequestDelete();
    }
}
