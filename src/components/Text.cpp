#include "components/Text.h"

#include "Camera.h"
#include "Game.h"
#include "resources/Resources.h"

Text::Text(GameObject& gameObject, std::string text, SDL_Color color,
           Style style, std::string fontFile, int fontSize)
    : Component{gameObject},
      mTexture{nullptr},
      mText{text},
      mFontFile{fontFile},
      mFontSize{fontSize},
      mStyle{style},
      mColor{color} {
    mFont = Resources::GetFont(mFontFile, mFontSize);

    RemakeTexture();
}

void Text::Update(float dt) {
    mBlinkTimer += dt;
    if (mBlinkDelay > 0 && mBlinkTimer > mBlinkDelay) {
        mBlinkTimer -= mBlinkDelay;
        mShow = !mShow;
    }
}

void Text::Render() {
    if (!mTexture || !mShow) {
        return;
    }

    SDL_Rect source =
        Rect{0.0, 0.0, mGameObject.mBox.w, mGameObject.mBox.h}.toSDL();

    Rect rect = mGameObject.mBox - Camera::sPos;

    SDL_Rect target = rect.toSDL();

    SDL_RenderCopyEx(Game::GetRenderer(), mTexture, &source, &target,
                     mGameObject.mAngle, NULL, SDL_FLIP_NONE);
}

void Text::SetText(std::string text) {
    mText = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    mColor = color;
    RemakeTexture();
}

void Text::SetBackgroundColor(SDL_Color color) {
    mBackgroundColor = color;
    RemakeTexture();
}

void Text::SetStyle(Style style) {
    if (style == mStyle) {
        return;
    }

    mStyle = style;
    RemakeTexture();
}

void Text::SetFontFile(std::string fontFile) {
    if (fontFile == mFontFile) {
        return;
    }

    mFontFile = fontFile;

    mFont = Resources::GetFont(mFontFile, mFontSize);

    RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    if (fontSize == mFontSize) {
        return;
    }

    mFontSize = fontSize;

    mFont = Resources::GetFont(mFontFile, mFontSize);

    RemakeTexture();
}

void Text::RemakeTexture() {
    if (mTexture) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
    }

    SDL_Surface* surface = nullptr;

    if (mStyle == Style::SOLID) {
        surface = TTF_RenderText_Solid(mFont, mText.c_str(), mColor);
    } else if (mStyle == Style::SHADED) {
        surface = TTF_RenderText_Shaded(mFont, mText.c_str(), mColor,
                                        mBackgroundColor);
    } else if (mStyle == Style::BLENDED) {
        surface = TTF_RenderText_Blended(mFont, mText.c_str(), mColor);
    }

    if (!surface) {
        printf("Failed to render text to surface %s due to %s\n", mText.c_str(),
               TTF_GetError());
        return;
    }

    mTexture = SDL_CreateTextureFromSurface(Game::GetRenderer(), surface);

    if (mTexture == nullptr) {
        printf("Failed to render text to texture %s due to %s\n", mText.c_str(),
               TTF_GetError());
        return;
    }

    mGameObject.mBox.w = surface->w;
    mGameObject.mBox.h = surface->h;

    SDL_FreeSurface(surface);
}

Text::~Text() {
    if (mTexture) {
        SDL_DestroyTexture(mTexture);
    }
}