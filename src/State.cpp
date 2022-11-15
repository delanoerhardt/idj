#include "State.h"

#include <math.h>

#include "Face.h"
#include "Sound.h"
#include "util/Vec2.h"

State::State()
    : mObjects{}, mMusic{"assets/audio/stageState.ogg"}, mQuitRequested(false) {
    GameObject* windowObject = new GameObject(0, 0);

    Sprite* backgroundSprite =
        new Sprite(*windowObject, "assets/img/ocean.jpg");

    windowObject->AddComponent(backgroundSprite);

    mObjects.emplace_back(windowObject);

    mMusic.Play();
}

bool State::QuitRequested() { return mQuitRequested; }

void State::LoadAssets() {}

void State::Update(float dt) {
    Input();

    for (int i = 0; i < mObjects.size(); i++) {
        mObjects[i]->Update(dt);

        if (mObjects[i]->IsDead()) {
            mObjects.erase(mObjects.begin() + i);
        }
    }

    if (SDL_QuitRequested()) {
        mQuitRequested = true;
    }
}

void State::Render() {
    for (int i = 0; i < mObjects.size(); i++) {
        mObjects[i]->Render();
    }
}

void State::Input() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            mQuitRequested = true;
            break;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;
            for (int i = mObjects.size() - 1; i >= 0; --i) {
                auto box = mObjects[i]->mBox;

                if (box.Contains(mouseX, mouseY)) {
                    Face* face = (Face*)mObjects[i]->GetComponent("Face");

                    if (face != nullptr) {
                        face->Damage(std::rand() % 10 + 10);

                        break;
                    }
                }
            }
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                mQuitRequested = true;

                break;
            } else if (event.key.keysym.sym == SDLK_SPACE) {
                int mouseX, mouseY;

                SDL_GetMouseState(&mouseX, &mouseY);

                Vec2 pos =
                    Vec2(mouseX, mouseY) +
                    Vec2(200, 0).Rotate(-M_PI + M_PI * (rand() % 1001) / 500.0);

                AddObject((int)pos.x, (int)pos.y);
            }
        }
    }
}

void State::AddObject(int x, int y) {
    GameObject* enemy = new GameObject(x, y);

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
