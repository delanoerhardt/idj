#include "GameObject.h"

void GameObject::Update(float dt) {
    for (auto it = mComponents.begin(); it != mComponents.end(); it++) {
        (*it)->Update(dt);
    }
}

void GameObject::Render() {
    for (auto it = mComponents.begin(); it != mComponents.end(); it++) {
        (*it)->Render();
    }
}

bool GameObject::IsDead() { return mIsDead; }

void GameObject::RequestDelete() { mIsDead = true; }

void GameObject::AddComponent(Component* component) {
    mComponents.push_back(component);
}

void GameObject::RemoveComponent(Component* component) {
    for (auto it = mComponents.begin(); it != mComponents.end(); it++) {
        if (*it == component) {
            delete component;
            mComponents.erase(it);
            return;
        }
    }
}

Component* GameObject::GetComponent(std::string type) {
    for (auto it = mComponents.begin(); it != mComponents.end(); it++) {
        if ((*it)->Is(type)) {
            return *it;
        }
    }

    return nullptr;
}

GameObject::~GameObject() {
    for (int i = mComponents.size() - 1; i >= 0; i--) {
        delete mComponents[i];
    }

    mComponents.clear();
}
