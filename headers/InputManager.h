#pragma once

#include <cstdint>
#include <unordered_map>

#include "util/Vec2.h"

typedef struct {
    uint32_t timestamp;
    uint32_t changedInTick;
    int mouseX;
    int mouseY;
    bool state;
    bool handled;
} ButtonState;

typedef struct {
    uint32_t timestamp;
    uint32_t changedInTick;
    bool state;
} KeyState;

class InputManager {
public:
    static void Update();

    static KeyState& GetKeyState(int key);

    static bool KeyPressed(int key);

    static bool KeyReleased(int key);

    static bool IsKeyDown(int key);

    static ButtonState& GetButtonState(int button);

    static bool ButtonPressed(int button, bool ignoreHandled = true);

    static bool ButtonReleased(int button, bool ignoreHandled = true);

    static bool IsButtonDown(int button, bool ignoreHandled = true);

    static void SetButtonHandled(ButtonState& buttonState, bool handled = true);

    static int GetMouseX();

    static int GetMouseY();

    static bool QuitRequested();

    static uint32_t sCurrendUpdateTick;

private:
    static bool sQuitRequested;

    static ButtonState sMouseState[6];

    static int sMouseX;
    static int sMouseY;

    static std::unordered_map<int, KeyState> sKeyboardState;
};
