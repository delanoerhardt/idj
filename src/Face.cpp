#include "Face.h"

#include "Sound.h"

Face::Face(GameObject& gameObject) : Component(gameObject), mHitpoints{30} {}

void Face::Damage(int damage) {
    mHitpoints -= damage;

    if (mHitpoints <= 0) {
        mGameObject.RequestDelete();

        Sound* sound = (Sound*)mGameObject.GetComponent("Sound");

        if (sound != nullptr) sound->Play();
    }
}

void Face::Update(float dt) {}

void Face::Render() {}

bool Face::Is(std::string type) { return type == "Face"; }
