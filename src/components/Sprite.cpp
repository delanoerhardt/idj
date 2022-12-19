#include "components/Sprite.h"

#include "Camera.h"
#include "Game.h"
#include "resources/Resources.h"

Sprite::Sprite(GameObject& gameObject, int frameCount, float frameTime)
    : Component{gameObject},
      mTexture{nullptr, 0, 0},
      mScale{1, 1},
      mFrameCount{frameCount},
      mFrameTime{frameTime} {}

Sprite::Sprite(GameObject& gameObject, std::string file, int frameCount,
               float frameTime)
    : Sprite{gameObject, frameCount, frameTime} {
    Open(file);
}

void Sprite::Open(std::string file) {
    mTexture = Resources::GetImage(file);

    SetClip(0, 0, mTexture.width / mFrameCount, mTexture.height);

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

    mScale = Vec2(scaleX, scaleY);

    mGameObject.mBox.x -= xSizeDiff / 2;
    mGameObject.mBox.x -= ySizeDiff / 2;
    mGameObject.mBox.w = GetWidth();
    mGameObject.mBox.h = GetHeight();
}

Vec2 Sprite::GetScale() { return Vec2{mScale}; }

void Sprite::SetFrame(int frame) {
    mCurrentFrame = frame;
    mClipRect.x = mCurrentFrame * (mTexture.width / mFrameCount);
}

void Sprite::SetFrameCount(int frameCount) {
    mFrameCount = frameCount;
    mClipRect.w = mTexture.width / mFrameCount;
    SetFrame(0);
}

void Sprite::SetFrameTime(float frameTime) { mFrameTime = frameTime; }

void Sprite::Update(float dt) {
    if (mLimitedLifespan) {
        mLifespan -= dt;
        if (mLifespan <= 0) {
            mGameObject.RequestDelete();
            return;
        }
    }

    mTimeElapsed += dt;

    if (mTimeElapsed > mFrameTime) {
        mTimeElapsed -= mFrameTime;
        SetFrame((mCurrentFrame + 1) % mFrameCount);
    }
}

void Sprite::Render() {
    if (mTexture.sdlTexture == nullptr) {
        return;
    }

    Vec2 cameraPos = Camera::sPos;

    Rect rect = mGameObject.mBox - cameraPos;

    SDL_Rect target = rect.toSDL();

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), mTexture.sdlTexture,
                     &mClipRect, &target, mGameObject.mAngle * RAD2DEG, NULL,
                     SDL_FLIP_NONE);
}

bool Sprite::IsOpen() { return mTexture.sdlTexture != nullptr; }

Sprite::~Sprite() {}
