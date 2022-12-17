#include "util/Vec2.h"

#include "util/Rect.h"

Vec2 Vec2::operator+=(const Rect &rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vec2 Vec2::operator-=(const Rect &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}