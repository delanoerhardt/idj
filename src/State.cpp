#include "State.h"

#include <math.h>

#include "Camera.h"
#include "components/Alien.h"
#include "components/CameraFollower.h"
#include "components/Sound.h"
#include "components/TileMap.h"
#include "resources/InputManager.h"
#include "resources/TileSet.h"
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

    for (t_objects::size_type i = 0; i < mObjects.size(); i++) {
        mObjects[i]->Update(dt);

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
    for (t_objects::size_type i = 0; i < mObjects.size(); i++) {
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
    for (auto it = mObjects.begin(); it != mObjects.end(); it++) {
        if (it->get() == gameObject) {
            return std::weak_ptr(*it);
        }
    }

    return std::weak_ptr<GameObject>{};
}

State::~State() { mObjects.clear(); }
