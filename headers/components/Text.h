#pragma once

#include "Component.h"

#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

class Text : public Component {
public:
    enum Style { SOLID, SHADED, BLENDED };

    Text(GameObject& gameObject, std::string text,
         SDL_Color color = SDL_Color{0, 0, 0, 0}, Style style = Style::BLENDED,
         std::string fontFile = "assets/font/Call me maybe.ttf",
         int fontSize = 16);

    virtual void Update(float dt);
    virtual void Render();
    virtual bool Is(std::string type) { return type == "Text"; }

    void SetText(std::string text);
    void SetColor(SDL_Color color);
    void SetBackgroundColor(SDL_Color color);
    void SetStyle(Style style);
    void SetFontFile(std::string fontFile);
    void SetFontSize(int fontSize);

    void SetBlinkDelay(int blinkDelay) {
        mBlinkDelay = blinkDelay;

        if (mBlinkDelay < 0) {
            mShow = true;
        }
    }

    ~Text();

private:
    void RemakeTexture();

    TTF_Font* mFont;
    SDL_Texture* mTexture;

    int mWidth, mHeight;

    std::string mText;
    std::string mFontFile;
    int mFontSize;
    Style mStyle;
    SDL_Color mColor;

    SDL_Color mBackgroundColor = SDL_Color{0, 0, 0, 255};

    float mBlinkDelay = -1;
    float mBlinkTimer = 0;
    bool mShow = true;
};