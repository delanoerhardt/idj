#include "Face.h"

#include "InputManager.h"
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

void Face::Update(float dt) {
    if (InputManager::ButtonPressed(SDL_BUTTON_LEFT)) {
        ButtonState& button = InputManager::GetButtonState(SDL_BUTTON_LEFT);

        auto box = mGameObject.mBox;

        if (box.Contains(button.mouseX, button.mouseY)) {
            Damage(std::rand() % 10 + 10);
            InputManager::SetButtonHandled(button);
        }
    }
}

void Face::Render() {}

bool Face::Is(std::string type) { return type == "Face"; }
