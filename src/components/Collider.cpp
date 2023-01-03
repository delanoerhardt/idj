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

    Vec2 initialPos =
        mGameObject.mBox.Center() - Vec2{mBox.w / 2, mBox.h / 2}.Rotate(angle);
    initialPos -= Camera::sPos;

    Vec2 widthVec = Vec2{mBox.w, 0.0}.Rotate(angle);
    Vec2 heightVec = Vec2{0.0, mBox.h}.Rotate(angle);

    Vec2 point = initialPos;
    points[0] = {(int)point.x, (int)point.y};
    points[4] = {(int)point.x, (int)point.y};

    point = initialPos + widthVec;
    points[1] = {(int)point.x, (int)point.y};

    point = initialPos + widthVec + heightVec;
    points[2] = {(int)point.x, (int)point.y};

    point = initialPos + heightVec;
    points[3] = {(int)point.x, (int)point.y};

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0,
                           SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
}