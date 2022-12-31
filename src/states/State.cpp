#include "states/State.h"

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

void State::Render() { RenderArray(); }

void State::Start() {
    LoadAssets();

    for (uint64_t i = 0; i < mObjects.size(); i++) {
        mObjects[i]->Start();
    }

    mStarted = true;
}

void State::Pause() {}

void State::Resume() {}

void State::StartArray() {
    for (uint64_t i = 0; i < mObjects.size(); i++) {
        mObjects[i]->Start();
    }
}

void State::UpdateArray(float dt) {
    for (uint64_t i = 0; i < mObjects.size(); i++) {
        mObjects[i]->Update(dt);
    }
}

void State::UpdateDeadArray() {
    for (uint64_t i = 0; i < mObjects.size(); i++) {
        if (mObjects[i]->IsDead()) {
            mObjects.erase(mObjects.begin() + i);
        }
    }
}

void State::RenderArray() {
    for (uint64_t i = 0; i < mObjects.size(); i++) {
        mObjects[i]->Render();
    }
}
