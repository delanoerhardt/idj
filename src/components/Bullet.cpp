#include "components/Bullet.h"

#include "components/Collider.h"
#include "components/Sprite.h"

Bullet::Bullet(GameObject& gameObject, float angle, float speed, int damage,
               float maxDistance, std::string spriteFilePath, float frameCount,
               float frameTime)
    : Component{gameObject}, mDamage{damage}, mDistanceLeft{maxDistance} {
    Sprite* sprite =
        new Sprite(gameObject, spriteFilePath, frameCount, frameTime);

    gameObject.mAngle = angle;

    gameObject.AddComponent(sprite);

    Collider* collider = new Collider(gameObject);

    mGameObject.AddComponent(collider);

    mSpeed = Vec2(1, 0).Rotate(angle) * speed;
}

Bullet::Bullet(GameObject& gameObject, Vec2 destination, float speed,
               int damage, float maxDistance, std::string spriteFilePath,
               float frameCount, float frameTime)
    : Component{gameObject}, mDamage{damage}, mDistanceLeft{maxDistance} {
    Sprite* sprite =
        new Sprite(gameObject, spriteFilePath, frameCount, frameTime);

    gameObject.mAngle = destination.AngleBetween(mGameObject.mBox.Center());

    gameObject.AddComponent(sprite);

    Collider* collider = new Collider(gameObject);

    mGameObject.AddComponent(collider);

    mSpeed = (destination - gameObject.mBox.Center()).Normalized() * speed;
}

void Bullet::Update(float dt) {
    mGameObject.mBox += mSpeed * dt;

    mDistanceLeft -= mSpeed.Length() * dt;
    if (mDistanceLeft < 0) {
        mGameObject.RequestDelete();
    }
}

void Bullet::NotifyCollision(GameObject& other) {
    if (other.GetComponent("Bullet")) {
        return;
    }

    bool isPlayer = other.GetComponent("PenguinBody") ||
                    other.GetComponent("PenguinCannon");

    if (isPlayer ^ mTargetsPlayer) {
        return;
    }

    mGameObject.RequestDelete();
}
