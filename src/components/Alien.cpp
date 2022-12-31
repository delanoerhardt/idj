#include "components/Alien.h"

#include "Camera.h"
#include "Game.h"
#include "components/Bullet.h"
#include "components/Collider.h"
#include "components/Minion.h"
#include "components/Sound.h"
#include "resources/InputManager.h"

#define ALIEN_SPEED 250
#define ALIEN_MIN_DISTANCE_TARGET 2

#define MOVE_COOLDOWN 3

int Alien::alienCount = 0;

Alien::Alien(GameObject& gameObject, int minionAmount)
    : Component{gameObject},
      mSpeed{},
      mHp{30},
      mMinionAmount{minionAmount},
      mState{Alien::State::RESTING},
      mDestination{GetPlayerPosition()} {
    Sprite* sprite = new Sprite{gameObject, "assets/img/alien.png"};

    gameObject.AddComponent(sprite);

    Collider* collider = new Collider(gameObject);

    mGameObject.AddComponent(collider);

    mRestTimer.Update((rand() % (MOVE_COOLDOWN * 1000)) / 1000.0);

    alienCount++;
}

void Alien::Start() {
    auto alienPtr = Game::GetCurrentState().GetObject(&mGameObject);

    float arcAngle = (M_PI * 2) / mMinionAmount;

    for (int i = 0; i < mMinionAmount; i++) {
        GameObject* minionObject = new GameObject();
        mMinionArray.push_back(Game::GetCurrentState().AddObject(minionObject));

        minionObject->AddComponent(
            new Minion(*minionObject, alienPtr, i * arcAngle));
    }
}

void Alien::Update(float dt) {
    if (mHp <= 0) {
        mGameObject.RequestDelete();

        CreateExplosion();

        return;
    }

    mGameObject.mAngle -= 0.007;

    if (mState == Alien::State::MOVING) {
        Vec2 movementDirection = mDestination - mGameObject.mBox.Center();

        mGameObject.mBox += movementDirection.Normalized() * (ALIEN_SPEED * dt);

        Vec2 newMovementDirection = mDestination - mGameObject.mBox.Center();

        if (movementDirection.DotProduct(newMovementDirection) <= 0) {
            mGameObject.mBox.SetCenterTo(mDestination);

            auto l = mMinionArray[rand() % mMinionArray.size()].lock();

            if (l) {
                Minion* minion = (Minion*)l->GetComponent("Minion");
                minion->Shoot(GetPlayerPosition());
            }

            mState = Alien::State::RESTING;
            mRestTimer.Restart();
        }
    } else if (mState == Alien::State::RESTING) {
        mRestTimer.Update(dt);

        if (mRestTimer.Get() >= MOVE_COOLDOWN) {
            mDestination = GetPlayerPosition();
            mState = Alien::State::MOVING;
        }
    }
}

void Alien::NotifyCollision(GameObject& other) {
    Bullet* bullet = (Bullet*)other.GetComponent("Bullet");

    if (bullet && !bullet->mTargetsPlayer) {
        mHp -= bullet->mDamage;
    }
}

void Alien::CreateExplosion() {
    GameObject* explosionObject = new GameObject();

    Sprite* sprite =
        new Sprite{*explosionObject, "assets/img/aliendeath.png", 4, 0.2};

    sprite->SetLifespan(0.8);

    explosionObject->CenterAt(mGameObject.mBox.Center());
    explosionObject->AddComponent(sprite);

    Sound* sound = new Sound{*explosionObject, "assets/audio/boom.wav"};
    sound->Play();

    explosionObject->AddComponent(sound);

    Game::GetCurrentState().AddObject(explosionObject);
}
