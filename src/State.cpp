#include "State.h"

#include <math.h>

#include "Camera.h"
#include "components/CameraFollower.h"
#include "components/Face.h"
#include "components/Sound.h"
#include "components/TileMap.h"
#include "resources/InputManager.h"
#include "resources/TileSet.h"
#include "util/Vec2.h"

TileMap* tileMap;

State::State()
    : mObjects{}, mMusic{"assets/audio/stageState.ogg"}, mQuitRequested(false) {
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

    mMusic.Play();
}

bool State::QuitRequested() { return mQuitRequested; }

void State::LoadAssets() {}

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

    if (InputManager::KeyPressed(SDLK_SPACE)) {
        int mouseX = InputManager::GetMouseX();
        int mouseY = InputManager::GetMouseY();

        Vec2 pos = Vec2(mouseX, mouseY) +
                   Vec2(200, 0).Rotate(-M_PI + M_PI * (rand() % 1001) / 500.0);

        AddObject((int)pos.x, (int)pos.y);
    }
}

void State::Render() {
    for (t_objects::size_type i = 0; i < mObjects.size(); i++) {
        mObjects[i]->Render();
    }
}

void State::AddObject(int x, int y) {
    Vec2 cameraPos = Camera::sPos;

    GameObject* enemy = new GameObject(x + cameraPos.x, y + cameraPos.y);

    Sprite* sprite = new Sprite(*enemy, "assets/img/penguinface.png");
    Sound* sound = new Sound(*enemy, "assets/audio/boom.wav");
    Face* face = new Face(*enemy);

    enemy->mBox.x -= enemy->mBox.w / 2;
    enemy->mBox.y -= enemy->mBox.h / 2;

    enemy->AddComponent(sprite);
    enemy->AddComponent(sound);
    enemy->AddComponent(face);

    mObjects.emplace_back(enemy);
}

State::~State() { mObjects.clear(); }
