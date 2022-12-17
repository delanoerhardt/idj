#include "components/Sprite.h"

#include "Camera.h"
#include "Game.h"
#include "resources/Resources.h"

Sprite::Sprite(GameObject& gameObject)
    : Component{gameObject}, mTexture{nullptr, 0, 0}, mScale{1, 1} {}

Sprite::Sprite(GameObject& gameObject, std::string file) : Sprite{gameObject} {
    Open(file);
}

void Sprite::Open(std::string file) {
    mTexture = Resources::GetImage(file);

    SetClip(0, 0, mTexture.width, mTexture.height);

    mGameObject.mBox.w = GetWidth();
    mGameObject.mBox.h = GetHeight();
}

void Sprite::SetClip(int x, int y, int w, int h) {
    mClipRect = SDL_Rect{x, y, w, h};
}

void Sprite::SetScale(float scaleX, float scaleY) {
    float xScaleDiff = mScale.x - scaleX;
    float yScaleDiff = mScale.y - scaleY;

    int xSizeDiff = xScaleDiff * mTexture.width;
    int ySizeDiff = yScaleDiff * mTexture.height;

    mGameObject.mBox -= Vec2(xSizeDiff, ySizeDiff) / 2;

    mScale = Vec2(scaleX, scaleY);
}

Vec2 Sprite::GetScale() { return Vec2{mScale}; }

void Sprite::Render() {
    if (mTexture.sdlTexture == nullptr) {
        return;
    }

    Vec2 cameraPos = Camera::sPos;

    Rect rect = mGameObject.mBox - cameraPos;

    SDL_Rect target = rect.Scale(mScale.x, mScale.y).toSDL();

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), mTexture.sdlTexture,
                     &mClipRect, &target, mAngleDeg, NULL, SDL_FLIP_NONE);
}

bool Sprite::IsOpen() { return mTexture.sdlTexture != nullptr; }

Sprite::~Sprite() {}
