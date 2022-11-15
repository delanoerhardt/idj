#pragma once

#include <math.h>

class Vec2 {
public:
    float x, y;

    Vec2(float x, float y) : x{x}, y{y} {}

    Vec2 &Rotate(float angle) {
        float x1 = x * cos(angle) - y * sin(angle);
        float y1 = x * sin(angle) + y * cos(angle);

        this->x = x1;
        this->y = y1;
        return *this;
    }

    Vec2 operator+=(const Vec2 &added) {
        x += added.x;
        y += added.y;
        return *this;
    }

    friend Vec2 operator+(Vec2 lhs, const Vec2 &added) {
        lhs += added;
        return lhs;
    }
};
