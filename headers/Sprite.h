#pragma once

#include <string>

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

class Sprite {
public:
    Sprite();

    Sprite(std::string file);

    ~Sprite();

    void Open(std::string file);

    void SetClip(int x, int y, int w, int h);

    void Render(int x, int y);

    int GetWidth();

    int GetHeight();

    bool IsOpen();

private:
    SDL_Texture *mTexture;
    int mWidth;
    int mHeight;
    SDL_Rect mClipRect;
};
