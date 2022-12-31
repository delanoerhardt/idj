#include "states/StageState.h"

#include <math.h>

#include "Camera.h"
#include "Game.h"
#include "components/Alien.h"
#include "components/CameraFollower.h"
#include "components/Collider.h"
#include "components/PenguinBody.h"
#include "components/Sound.h"
#include "components/TileMap.h"
#include "resources/GameData.h"
#include "resources/InputManager.h"
#include "resources/TileSet.h"
#include "states/EndState.h"
#include "util/CollisionDetection.h"
#include "util/Vec2.h"

TileMap* tileMap;

StageState::StageState() : State{}, mMusic{"assets/audio/stageState.ogg"} {
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

    int alienAmount = (rand() % 3) + 2;

    for (int i = 0; i < alienAmount; i++) {
        int x = (rand() % 1308) - 50;
        int y = (rand() % 1180) - 50;

        GameObject* alienObject = new GameObject(x, y);
        alienObject->AddComponent(new Alien(*alienObject, (rand() % 5) + 2));

        mObjects.emplace_back(alienObject);
    }

    GameObject* penguinObject = new GameObject(704, 640);
    penguinObject->AddComponent(new PenguinBody(*penguinObject));

    mObjects.emplace_back(penguinObject);

    mPenguinPtr = mObjects[mObjects.size() - 1];

    Camera::Follow(penguinObject);

    mMusic.Play();
}

void StageState::Update(float dt) {
    LOGLINE();
    Camera::Update(dt);

    LOGLINE();
    UpdateArray(dt);
    LOGLINE();

    CheckCollisions();
    LOGLINE();

    UpdateDeadArray();
    LOGLINE();

    if (InputManager::QuitRequested() ||
        InputManager::KeyPressed(SDLK_ESCAPE)) {
        LOGLINE();
        mPopRequested = true;
    }

    if (Alien::alienCount <= 0) {
        LOGLINE();
        GameData::playerVictory = true;

        mPopRequested = true;
        Game::Push(new EndState());
    } else if (mPenguinPtr->IsDead()) {
        LOGLINE();
        GameData::playerVictory = false;

        mPopRequested = true;
        Game::Push(new EndState());
    }
}

void StageState::CheckCollisions() {
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

void StageState::Pause() { mMusic.Stop(); }
