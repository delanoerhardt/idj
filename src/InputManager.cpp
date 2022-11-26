#include "InputManager.h"

#define INCLUDE_SDL
#include "SDL_include.h"

uint32_t InputManager::sCurrendUpdateTick = 0;

bool InputManager::sQuitRequested = false;

ButtonState InputManager::sMouseState[6] = {};

int InputManager::sMouseX = 0;
int InputManager::sMouseY = 0;

std::unordered_map<int, KeyState> InputManager::sKeyboardState;

void InputManager::Update() {
    sCurrendUpdateTick++;

    sQuitRequested = false;

    SDL_Event event;
    SDL_MouseButtonEvent button;

    SDL_KeyboardEvent key;
    SDL_Keycode keySym;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                sQuitRequested = true;
                break;

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                button = event.button;

                sMouseState[button.button].state = button.state;
                sMouseState[button.button].timestamp = button.timestamp;

                sMouseState[button.button].mouseX = button.x;
                sMouseState[button.button].mouseY = button.y;

                sMouseState[button.button].changedInTick = sCurrendUpdateTick;
                sMouseState[button.button].handled = false;
                break;

            case SDL_KEYDOWN:
            case SDL_KEYUP:
                key = event.key;

                if (key.repeat) {
                    break;
                }

                keySym = key.keysym.sym;

                sKeyboardState[keySym].state = key.state;
                sKeyboardState[keySym].timestamp = key.timestamp;
                sKeyboardState[keySym].changedInTick = sCurrendUpdateTick;
                break;

            default:
                break;
        }
    }

    SDL_GetMouseState(&sMouseX, &sMouseY);
}

KeyState& InputManager::GetKeyState(int key) { return sKeyboardState[key]; }

bool InputManager::KeyPressed(int key) {
    KeyState keyState = sKeyboardState[key];

    if (keyState.changedInTick == sCurrendUpdateTick) {
        return keyState.state;
    }

    return false;
}

bool InputManager::KeyReleased(int key) {
    KeyState keyState = sKeyboardState[key];

    if (keyState.changedInTick == sCurrendUpdateTick) {
        return !keyState.state;
    }

    return false;
}

bool InputManager::IsKeyDown(int key) { return sKeyboardState[key].state; }

ButtonState& InputManager::GetButtonState(int button) {
    return sMouseState[button];
}

bool InputManager::ButtonPressed(int button, bool ignoreHandled) {
    ButtonState buttonState = sMouseState[button];

    if (buttonState.changedInTick == sCurrendUpdateTick) {
        if (ignoreHandled) {
            return buttonState.state && !sMouseState[button].handled;
        }

        return buttonState.state;
    }

    return false;
}

bool InputManager::ButtonReleased(int button, bool ignoreHandled) {
    ButtonState buttonState = sMouseState[button];

    if (buttonState.changedInTick == sCurrendUpdateTick) {
        if (ignoreHandled) {
            return !buttonState.state && !sMouseState[button].handled;
        }

        return !buttonState.state;
    }

    return false;
}

bool InputManager::IsButtonDown(int button, bool ignoreHandled) {
    if (ignoreHandled) {
        return sMouseState[button].state && !sMouseState[button].handled;
    }

    return sMouseState[button].state;
}

void InputManager::SetButtonHandled(ButtonState& buttonState, bool handled) {
    buttonState.handled = handled;
}

int InputManager::GetMouseX() { return sMouseX; }

int InputManager::GetMouseY() { return sMouseY; }

bool InputManager::QuitRequested() { return sQuitRequested; }
