#include "Sprite.h"

#include "Game.h"

Sprite::Sprite() : mTexture{nullptr} {}

Sprite::Sprite(std::string file) : Sprite() { Open(file); }

void Sprite::Open(std::string file) {
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
    }

    mTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    if (mTexture == NULL) {
        printf("Failed to open Sprite %s due to %s\n", file.c_str(),
               SDL_GetError());
        exit(1);
    }

    int errorValue =
        SDL_QueryTexture(mTexture, nullptr, nullptr, &mWidth, &mHeight);

    if (errorValue != 0) {
        printf("Erro ao query textura\n%s\n", SDL_GetError());
    }

    printf("%d, %d\n", mWidth, mHeight);

    SetClip(0, 0, mWidth, mHeight);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    mClipRect = SDL_Rect{x, y, w, h};
}

void Sprite::Render(int x, int y) {
    if (mTexture == nullptr) {
        return;
    }

    SDL_Rect target{x, y, mWidth, mHeight};
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), mTexture, &mClipRect,
                   &target);
}

int Sprite::GetWidth() { return mWidth; }

int Sprite::GetHeight() { return mHeight; }

bool Sprite::IsOpen() { return mTexture != nullptr; }

Sprite::~Sprite() {
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
    }
}