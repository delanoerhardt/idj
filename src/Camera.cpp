#include "Camera.h"

#include "Constants.h"
#include "resources/InputManager.h"

Vec2 Camera::sPos;
Vec2 Camera::sSpeed;

GameObject* Camera::sFocus;

void Camera::Follow(GameObject* newFocus) { sFocus = newFocus; }

void Camera::Unfollow() { sFocus = nullptr; }

void Camera::Update(float dt) {
    if (sFocus != nullptr) {
        sPos.x = sFocus->mBox.x;
        sPos.y = sFocus->mBox.y;

        return;
    }

    sSpeed.x = sSpeed.y = 0;

    if (InputManager::IsKeyDown(SDLK_a)) {
        sSpeed.x -= CAMERA_SPEED;
    }

    if (InputManager::IsKeyDown(SDLK_d)) {
        sSpeed.x += CAMERA_SPEED;
    }

    if (InputManager::IsKeyDown(SDLK_w)) {
        sSpeed.y -= CAMERA_SPEED;
    }

    if (InputManager::IsKeyDown(SDLK_s)) {
        sSpeed.y += CAMERA_SPEED;
    }

    sPos += sSpeed * dt;
}