#pragma once

#include "Component.h"

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

class ColorSprite : public Component {
public:
    ColorSprite(GameObject& gameObject, uint8_t r, uint8_t g, uint8_t b,
                uint8_t a = 255);

    ColorSprite* SetFill(bool fill) {
        mFill = fill;
        return this;
    }

    virtual void Render();

    virtual bool Is(std::string type) { return type == "Rect"; }

    uint8_t r, g, b, a;
    bool mFill = false;

    virtual ~ColorSprite() {}
};
