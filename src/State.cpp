#include "State.h"

#include <math.h>

#include "Camera.h"
#include "components/Alien.h"
#include "components/CameraFollower.h"
#include "components/Collider.h"
#include "components/PenguinBody.h"
#include "components/Sound.h"
#include "components/TileMap.h"
#include "resources/InputManager.h"
#include "resources/TileSet.h"
#include "util/CollisionDetection.h"
#include "util/Vec2.h"

TileMap* tileMap;

State::State() : mObjects{}, mMusic{"assets/audio/stageState.ogg"} {
    TileSet* tileSet = new TileSet(64, 64, "assets/img/tileset.png");

    GameObject* windowObject = new GameObject(0, 0);

    Sprite* backgroundSprite =
        new Sprite(*windowObject, "assets/img/ocean.jpg");
    windowObject->AddComponent(backgroundSprite);
    windowObject->AddComponent(new CameraFollower(*windowObject));

    mObjects.emplace_back(windowObject);

    GameObject* cameraObject = new GameObject(0, 0);

    tileMap = new TileMap(*cameraObject, "assets/map/tileMap.txt", tileSet);
    cameraObject->AddComponent(tileMap);

    mObjects.emplace_back(cameraObject);

    GameObject* alienObject = new GameObject(512, 300);
    alienObject->AddComponent(new Alien(*alienObject, 4));

    mObjects.emplace_back(alienObject);

    GameObject* penguinObject = new GameObject(704, 640);
    penguinObject->AddComponent(new PenguinBody(*penguinObject));

    mObjects.emplace_back(penguinObject);

    Camera::Follow(penguinObject);

    mMusic.Play();
}

bool State::QuitRequested() { return mQuitRequested; }

void State::LoadAssets() {}

void State::Start() {
    LoadAssets();

    for (uint64_t i = 0; i < mObjects.size(); i++) {
        mObjects[i]->Start();
    }

    mStarted = true;
}

void State::Update(float dt) {
    Camera::Update(dt);

    for (uint64_t i = 0; i < mObjects.size(); i++) {
        mObjects[i]->Update(dt);
    }

    CheckCollisions();

    for (uint64_t i = 0; i < mObjects.size(); i++) {
        if (mObjects[i]->IsDead()) {
            mObjects.erase(mObjects.begin() + i);
        }
    }

    if (InputManager::QuitRequested() ||
        InputManager::KeyPressed(SDLK_ESCAPE)) {
        mQuitRequested = true;
    }
}

void State::Render() {
    for (uint64_t i = 0; i < mObjects.size(); i++) {
        mObjects[i]->Render();
    }
}

std::weak_ptr<GameObject> State::AddObject(GameObject* gameObject) {
    std::shared_ptr<GameObject>& objectSharedPointer =
        mObjects.emplace_back(gameObject);

    if (mStarted) gameObject->Start();

    return std::weak_ptr(objectSharedPointer);
}

std::weak_ptr<GameObject> State::GetObject(GameObject* gameObject) {
    for (uint64_t i = 0; i < mObjects.size(); i++) {
        if (mObjects[i].get() == gameObject) {
            return std::weak_ptr(mObjects[i]);
        }
    }

    return std::weak_ptr<GameObject>{};
}

State::~State() { mObjects.clear(); }

void State::CheckCollisions() {
    Collider *collider1, *collider2;

    for (uint64_t i = 0; i < mObjects.size(); i++) {
        if (mObjects[i]->IsDead()) continue;

        collider1 = (Collider*)mObjects[i]->GetComponent("Collider");

        if (collider1 == nullptr) {
            continue;
        }

        for (uint64_t j = i + 1; j < mObjects.size(); j++) {
            if (mObjects[j]->IsDead()) continue;

            collider2 = (Collider*)mObjects[j]->GetComponent("Collider");

            if (collider2 == nullptr) {
                continue;
            }

            bool collided = CollisionDetection::IsColliding(
                collider1->mBox, collider2->mBox, collider1->mGameObject.mAngle,
                collider2->mGameObject.mAngle);

            if (collided) {
                collider1->mGameObject.NotifyCollision(collider2->mGameObject);
                collider2->mGameObject.NotifyCollision(collider1->mGameObject);
            }
        }
    }
}
