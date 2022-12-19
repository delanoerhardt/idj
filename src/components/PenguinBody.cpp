#include "components/PenguinBody.h"

#include "Camera.h"
#include "Game.h"
#include "components/Bullet.h"
#include "components/Collider.h"
#include "components/PenguinCannon.h"
#include "components/Sound.h"
#include "resources/InputManager.h"

#define PENGUIN_ACCELERATION 300

#define MAX_SPEED 500

#define ANGULAR_SPEED 4

PenguinBody* PenguinBody::sPlayer;

PenguinBody::PenguinBody(GameObject& gameObject)
    : Component{gameObject}, mHp{30} {
    Sprite* sprite = new Sprite(gameObject, "assets/img/penguin.png");

    mGameObject.AddComponent(sprite);

    Collider* collider = new Collider(gameObject);

    mGameObject.AddComponent(collider);

    PenguinBody::sPlayer = this;
}

PenguinBody::~PenguinBody() { PenguinBody::sPlayer = nullptr; }

void PenguinBody::Start() {
    State& state = Game::GetInstance().GetState();

    GameObject* penguinObject = new GameObject(mGameObject.mBox.Center());

    PenguinCannon* penguinCannon =
        new PenguinCannon(*penguinObject, state.GetObject(&mGameObject));

    penguinObject->AddComponent(penguinCannon);

    mPenguinCannon = state.AddObject(penguinObject);
}

void PenguinBody::Update(float dt) {
    auto penguinCannonPtr = mPenguinCannon.lock();

    if (!penguinCannonPtr) {
        mGameObject.RequestDelete();
        return;
    }

    if (mHp <= 0) {
        mGameObject.RequestDelete();
        penguinCannonPtr->RequestDelete();
        CreateExplosion();
        Camera::Unfollow();
        return;
    }

    if (InputManager::IsKeyDown(SDLK_w)) {
        mSpeed.x += dt * PENGUIN_ACCELERATION;
        if (mSpeed.x > MAX_SPEED) {
            mSpeed.x = MAX_SPEED;
        }
    }

    if (InputManager::IsKeyDown(SDLK_s)) {
        mSpeed.x -= dt * PENGUIN_ACCELERATION * 2;
        if (mSpeed.x < -(MAX_SPEED / 2)) {
            mSpeed.x = -(MAX_SPEED / 2);
        }
    }

    if (InputManager::IsKeyDown(SDLK_a)) {
        mAngle -= ANGULAR_SPEED * dt;
    }

    if (InputManager::IsKeyDown(SDLK_d)) {
        mAngle += ANGULAR_SPEED * dt;
    }

    mGameObject.mAngle = mAngle;

    mGameObject.mBox += mSpeed.Rotate(mAngle) * dt;
}

void PenguinBody::NotifyCollision(GameObject& other) {
    Bullet* bullet = (Bullet*)other.GetComponent("Bullet");

    if (bullet && bullet->mTargetsPlayer) {
        mHp -= bullet->mDamage;
    }
}

void PenguinBody::CreateExplosion() {
    GameObject* explosionObject = new GameObject();

    Sprite* sprite =
        new Sprite{*explosionObject, "assets/img/penguindeath.png", 5, 0.15};

    sprite->SetLifespan(0.75);

    explosionObject->CenterAt(mGameObject.mBox.Center());
    explosionObject->AddComponent(sprite);

    Sound* sound = new Sound{*explosionObject, "assets/audio/boom.wav"};
    sound->Play();

    explosionObject->AddComponent(sound);

    Game::GetInstance().GetState().AddObject(explosionObject);
}
