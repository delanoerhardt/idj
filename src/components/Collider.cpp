#include "components/Collider.h"

#include "Camera.h"
#include "Game.h"

void Collider::Update(float dt) {
    mBox = (mGameObject.mBox.ScaleCentered(mScale) + mOffset);
}

void Collider::Render() {
    float angle = mGameObject.mAngle;
    Vec2 center(mGameObject.mBox.Center());
    SDL_Point points[5];

    Vec2 centerCamera = center - Camera::sPos;

    Vec2 point = (Vec2(mBox.x, mBox.y) - center).Rotate(angle) + centerCamera;
    points[0] = {(int)point.x, (int)point.y};
    points[4] = {(int)point.x, (int)point.y};

    point =
        (Vec2(mBox.x + mBox.w, mBox.y) - center).Rotate(angle) + centerCamera;
    points[1] = {(int)point.x, (int)point.y};

    point = (Vec2(mBox.x + mBox.w, mBox.y + mBox.h) - center).Rotate(angle) +
            centerCamera;
    points[2] = {(int)point.x, (int)point.y};

    point =
        (Vec2(mBox.x, mBox.y + mBox.h) - center).Rotate(angle) + centerCamera;
    points[3] = {(int)point.x, (int)point.y};

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0,
                           SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
}