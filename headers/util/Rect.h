#pragma once

#include <sstream>

// Forward declaration
class Vec2;

#include "Vec2.h"

#define INCLUDE_SDL_IMAGE
#include "../SDL_include.h"

class Rect {
public:
    float x, y, w, h;

    Rect() : x{0}, y{0}, w{0}, h{0} {}

    Rect(int x, int y, int w, int h)
        : x{(float)x}, y{(float)y}, w{(float)w}, h{(float)h} {}

    Rect(float x, float y, float w, float h) : x{x}, y{y}, w{w}, h{h} {}

    Rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
        : x{(float)x}, y{(float)y}, w{(float)w}, h{(float)h} {}

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

    bool Contains(Vec2 &vector) { return Contains(vector.x, vector.y); }

    Vec2 Center() { return Vec2{x + w / 2, y + h / 2}; }

    Vec2 CenterDistance(Rect &rhs) { return this->Center() - rhs.Center(); }

    void SetCenterTo(const Vec2 &rhs) {
        x = rhs.x - w / 2;
        y = rhs.y - h / 2;
    }

    void SetCenterTo(float _x, float _y) {
        x = _x - w / 2;
        y = _y - h / 2;
    }

    void SetSize(float width, float height) {
        w = width;
        h = height;
    }

    void ClipTo(Rect rect);

    std::string toString() {
        std::stringstream ss;
        ss << "{ x: " << x << ", y: " << y << ", w: " << w << ", h: " << h
           << " }";
        return ss.str();
    }

    Rect Scale(float scaleX, float scaleY) {
        return Rect{x, y, w * scaleX, h * scaleY};
    }

    Rect Scale(Vec2 &scale) { return Rect{x, y, w * scale.x, h * scale.y}; }

    Rect ScaleCentered(Vec2 &scale) {
        return Rect{x + w / 2 * (1 - scale.x), y + h / 2 * (1 - scale.y),
                    w * scale.x, h * scale.y};
    }

    Rect operator+=(const Rect &rhs) {
        x += rhs.x;
        y += rhs.y;
        w += rhs.w;
        h += rhs.h;
        return *this;
    }

    Rect operator+=(const Vec2 &rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Rect operator+=(int rhs) {
        x += rhs;
        y += rhs;
        w += rhs;
        h += rhs;
        return *this;
    }

    Rect operator+=(float rhs) {
        x += rhs;
        x += rhs;
        x += rhs;
        x += rhs;
        return *this;
    }

    Rect operator-=(const Rect &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        w -= rhs.w;
        h -= rhs.h;
        return *this;
    }

    Rect operator-=(const Vec2 &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Rect operator-=(int rhs) {
        x -= rhs;
        y -= rhs;
        w -= rhs;
        h -= rhs;
        return *this;
    }

    Rect operator-=(float rhs) {
        x -= rhs;
        y -= rhs;
        w -= rhs;
        h -= rhs;
        return *this;
    }

    Rect operator*=(int rhs) {
        x *= rhs;
        y *= rhs;
        w *= rhs;
        h *= rhs;
        return *this;
    }

    Rect operator*=(float rhs) {
        x *= rhs;
        y *= rhs;
        w *= rhs;
        h *= rhs;
        return *this;
    }

    Rect operator/=(int rhs) {
        x /= rhs;
        y /= rhs;
        w /= rhs;
        h /= rhs;
        return *this;
    }

    Rect operator/=(float rhs) {
        x /= rhs;
        y /= rhs;
        w /= rhs;
        h /= rhs;
        return *this;
    }

    friend Rect operator+(Rect lhs, const Rect &rhs) {
        lhs += rhs;
        return lhs;
    }

    friend Rect operator+(Rect lhs, const Vec2 &rhs) {
        lhs += rhs;
        return lhs;
    }

    friend Rect operator+(Rect lhs, int rhs) {
        lhs += rhs;
        return lhs;
    }

    friend Rect operator+(Rect lhs, float rhs) {
        lhs += rhs;
        return lhs;
    }

    friend Rect operator-(Rect lhs, const Rect &rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend Rect operator-(Rect lhs, const Vec2 &rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend Rect operator-(Rect lhs, int rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend Rect operator-(Rect lhs, float rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend Rect operator*(Rect lhs, int rhs) {
        lhs *= rhs;
        return lhs;
    }

    friend Rect operator*(Rect lhs, float rhs) {
        lhs *= rhs;
        return lhs;
    }

    friend Rect operator/(Rect lhs, int rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend Rect operator/(Rect lhs, float rhs) {
        lhs /= rhs;
        return lhs;
    }
};
