#include "GameObject.h"

void GameObject::Start() {
    for (uint64_t i = 0; i < mComponents.size(); i++) {
        mComponents[i]->Start();
    }

    mStarted = true;
}

void GameObject::Update(float dt) {
    for (uint64_t i = 0; i < mComponents.size(); i++) {
        mComponents[i]->Update(dt);
    }
}

void GameObject::Render() {
    for (uint64_t i = 0; i < mComponents.size(); i++) {
        mComponents[i]->Render();
    }
}

bool GameObject::IsDead() { return mIsDead; }

void GameObject::RequestDelete() { mIsDead = true; }

void GameObject::AddComponent(Component* component) {
    mComponents.push_back(component);

    if (mStarted) component->Start();
}

void GameObject::RemoveComponent(Component* component) {
    for (uint64_t i = 0; i < mComponents.size(); i++) {
        if (mComponents[i] == component) {
            delete component;
            mComponents.erase(mComponents.begin() + i);
            return;
        }
    }
}

void GameObject::NotifyCollision(GameObject& other) {
    for (uint64_t i = 0; i < mComponents.size(); i++) {
        mComponents[i]->NotifyCollision(other);
    }
}

Component* GameObject::GetComponent(std::string type) {
    for (uint64_t i = 0; i < mComponents.size(); i++) {
        if (mComponents[i]->Is(type)) {
            return mComponents[i];
        }
    }

    return nullptr;
}

GameObject::~GameObject() {
    for (uint64_t i = mComponents.size(); i > 0; i--) {
        delete mComponents[i - 1];
    }

    mComponents.clear();
}
