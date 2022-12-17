#pragma once

#include <math.h>

#include <cstdint>
#include <sstream>

#define RAD2DEG (180 / M_PI)
#define DEG2RAD (1 / RAD2DEG)

// Forward declaration
class Rect;

class Vec2 {
public:
    float x, y;

    Vec2() : x{0}, y{0} {}

    Vec2(float x, float y) : x{x}, y{y} {}

    Vec2(int x, int y) : x{(float)x}, y{(float)y} {}

    Vec2(uint32_t x, uint32_t y) : x{(float)x}, y{(float)y} {}

    Vec2 &Rotate(float angle) {
        float cosAngle = cos(angle), sinAngle = sin(angle);

        float x1 = x * cosAngle - y * sinAngle;
        float y1 = x * sinAngle + y * cosAngle;

        this->x = x1;
        this->y = y1;
        return *this;
    }

    float Length() { return sqrt(x * x + y * y); }

    Vec2 Normalized() {
        float length = Length();
        if (length == 0) {
            return Vec2{0, 0};
        }
        return Vec2{x / length, y / length};
    }

    double Angle() { return atan2(y, x); }

    double AngleBetween(Vec2 rhs) { return atan2(y - rhs.y, x - rhs.x); }

    float DotProduct(Vec2 rhs) { return x * rhs.x + y * rhs.y; }

    std::string toString() {
        std::stringstream ss;
        ss << "{ x: " << x << ", y: " << y << " }";
        return ss.str();
    }

    Vec2 operator+=(const Vec2 &rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vec2 operator+=(const Rect &rhs);

    Vec2 operator+=(const int rhs) {
        x += rhs;
        y += rhs;
        return *this;
    }

    Vec2 operator+=(const float rhs) {
        x += rhs;
        y += rhs;
        return *this;
    }

    Vec2 operator-=(const Vec2 &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vec2 operator-=(const Rect &rhs);

    Vec2 operator-=(const int rhs) {
        x -= rhs;
        y -= rhs;
        return *this;
    }

    Vec2 operator-=(const float rhs) {
        x -= rhs;
        y -= rhs;
        return *this;
    }

    Vec2 operator*=(const int rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    Vec2 operator*=(const float rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    Vec2 operator/=(const int rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    Vec2 operator/=(const float rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    friend Vec2 operator+(Vec2 lhs, const Vec2 &rhs) {
        lhs += rhs;
        return lhs;
    }

    friend Vec2 operator+(Vec2 lhs, const Rect &rhs) {
        lhs += rhs;
        return lhs;
    }

    friend Vec2 operator+(Vec2 lhs, const int rhs) {
        lhs += rhs;
        return lhs;
    }

    friend Vec2 operator+(Vec2 lhs, const float rhs) {
        lhs += rhs;
        return lhs;
    }

    friend Vec2 operator-(Vec2 lhs, const Vec2 &rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend Vec2 operator-(Vec2 lhs, const Rect &rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend Vec2 operator-(Vec2 lhs, const int rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend Vec2 operator-(Vec2 lhs, const float rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend Vec2 operator*(Vec2 lhs, const int rhs) {
        lhs *= rhs;
        return lhs;
    }

    friend Vec2 operator*(Vec2 lhs, const float rhs) {
        lhs *= rhs;
        return lhs;
    }

    friend Vec2 operator/(Vec2 lhs, const int rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend Vec2 operator/(Vec2 lhs, const float rhs) {
        lhs /= rhs;
        return lhs;
    }
};
