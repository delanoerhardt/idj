#pragma once

#include <string>

#include "Component.h"
#include "GameObject.h"

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

class Sprite : public Component {
public:
    Sprite(GameObject& gameObject);

    Sprite(GameObject& gameObject, const char* file);

    void Open(const char* file);

    void SetClip(int x, int y, int w, int h);

    virtual void Update(float dt);

    virtual void Render();

    virtual bool Is(std::string type);

    bool IsOpen();

    virtual ~Sprite();

    int mWidth;
    int mHeight;

private:
    SDL_Texture* mTexture;
    SDL_Rect mClipRect;
};
