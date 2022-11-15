#pragma once

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

class Rect {
public:
    float x, y, w, h;

    Rect() : x{0}, y{0}, w{0}, h{0} {}
    Rect(int x, int y, int w, int h)
        : x{(float)x}, y{(float)y}, w{(float)w}, h{(float)h} {}
    Rect(float x, float y, float w, float h) : x{x}, y{y}, w{w}, h{h} {}

    Rect(SDL_Rect &sdlRect) {
        x = (float)sdlRect.x;
        y = (float)sdlRect.y;
        w = (float)sdlRect.w;
        h = (float)sdlRect.h;
    }

    SDL_Rect toSDL() { return SDL_Rect{(int)x, (int)y, (int)w, (int)h}; }

    bool Contains(float pointX, float pointY) {
        return pointX > x && pointX < x + w && pointY > y && pointY < y + h;
    }

    Rect operator+=(const Rect &added) {
        x += added.x;
        y += added.y;
        w += added.w;
        h += added.h;
        return *this;
    }

    Rect operator+=(int added) {
        x += added;
        y += added;
        w += added;
        h += added;
        return *this;
    }

    Rect operator+=(float added) {
        x += added;
        x += added;
        x += added;
        x += added;
        return *this;
    }

    Rect operator-=(const Rect &added) {
        x -= added.x;
        y -= added.y;
        w -= added.w;
        h -= added.h;
        return *this;
    }

    Rect operator-=(int added) {
        x -= added;
        y -= added;
        w -= added;
        h -= added;
        return *this;
    }

    Rect operator-=(float added) {
        x -= added;
        y -= added;
        w -= added;
        h -= added;
        return *this;
    }

    Rect operator*=(int added) {
        x *= added;
        y *= added;
        w *= added;
        h *= added;
        return *this;
    }

    Rect operator/=(int added) {
        x /= added;
        y /= added;
        w /= added;
        h /= added;
        return *this;
    }

    Rect operator*=(float added) {
        x *= added;
        y *= added;
        w *= added;
        h *= added;
        return *this;
    }

    Rect operator/=(float added) {
        x /= added;
        y /= added;
        w /= added;
        h /= added;
        return *this;
    }

    friend Rect operator+(Rect lhs, const Rect &added) {
        lhs += added;
        return lhs;
    }

    friend Rect operator+(Rect lhs, int added) {
        lhs += added;
        return lhs;
    }

    friend Rect operator+(Rect lhs, float added) {
        lhs += added;
        return lhs;
    }

    friend Rect operator-(Rect lhs, const Rect &added) {
        lhs -= added;
        return lhs;
    }

    friend Rect operator-(Rect lhs, int added) {
        lhs -= added;
        return lhs;
    }

    friend Rect operator-(Rect lhs, float added) {
        lhs -= added;
        return lhs;
    }

    friend Rect operator*(Rect lhs, int added) {
        lhs *= added;
        return lhs;
    }

    friend Rect operator*(Rect lhs, float added) {
        lhs *= added;
        return lhs;
    }

    friend Rect operator/(Rect lhs, int added) {
        lhs /= added;
        return lhs;
    }

    friend Rect operator/(Rect lhs, float added) {
        lhs /= added;
        return lhs;
    }
};
