#include "util/Rect.h"

void Rect::ClipTo(Rect rect) {
    Vec2 center = Center();

    float _x = center.x, _y = center.y;

    if (center.x < rect.x) {
        _x = rect.x;
    } else if (center.x > rect.x + rect.w) {
        _x = rect.x + rect.w;
    }

    if (center.y < rect.y) {
        _y = rect.y;
    } else if (center.y > rect.y + rect.h) {
        _y = rect.y + rect.h;
    }

    SetCenterTo(_x, _y);
}