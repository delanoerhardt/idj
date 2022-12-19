#pragma once

#include <string>

#include "Component.h"
#include "GameObject.h"
#include "resources/Texture.h"
#include "util/Vec2.h"

class Sprite : public Component {
public:
    Sprite(GameObject& gameObject, int frameCount = 1, float frameTime = 1);

    Sprite(GameObject& gameObject, std::string file, int frameCount = 1,
           float frameTime = 1);

    void Open(std::string file);

    void SetClip(int x, int y, int w, int h);

    void SetScale(float scaleX, float scaleY);

    Vec2 GetScale();

    void SetFrame(int frame);

    void SetFrameCount(int frameCount);

    void SetFrameTime(float frameTime);

    Sprite* SetLifespan(float lifespan) {
        mLifespan = lifespan;
        mLimitedLifespan = true;

        return this;
    }

    virtual void Update(float dt);

    virtual void Render();

    virtual bool Is(std::string type) { return type == "Sprite"; }

    bool IsOpen();

    virtual ~Sprite();

    float GetWidth() { return (mTexture.width * mScale.x) / mFrameCount; }

    float GetHeight() { return mTexture.height * mScale.y; }

    Texture mTexture;

private:
    Vec2 mScale;

    SDL_Rect mClipRect;

    int mFrameCount;

    int mCurrentFrame = 0;

    float mTimeElapsed = 0;

    float mFrameTime;

    float mLifespan;

    bool mLimitedLifespan = false;
};
