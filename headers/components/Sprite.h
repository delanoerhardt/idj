#pragma once

#include <string>

#include "Component.h"
#include "GameObject.h"
#include "resources/Texture.h"
#include "util/Vec2.h"

class Sprite : public Component {
public:
    Sprite(GameObject& gameObject);

    Sprite(GameObject& gameObject, std::string file);

    void Open(std::string file);

    void SetClip(int x, int y, int w, int h);

    void SetScale(float scaleX, float scaleY);

    Vec2 GetScale();

    virtual void Render();

    virtual bool Is(std::string type) { return type == "Sprite"; }

    bool IsOpen();

    virtual ~Sprite();

    float GetWidth() { return mTexture.width * mScale.x; }

    float GetHeight() { return mTexture.height * mScale.y; }

    Texture mTexture;

    float mAngleDeg = 0;

private:
    Vec2 mScale;
    SDL_Rect mClipRect;
};
