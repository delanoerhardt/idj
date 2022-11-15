#include "Sprite.h"

#include "Game.h"

Sprite::Sprite(GameObject& gameObject)
    : Component{gameObject}, mTexture{nullptr} {}

Sprite::Sprite(GameObject& gameObject, const char* file) : Sprite{gameObject} {
    Open(file);
}

void Sprite::Open(const char* file) {
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
    }

    mTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file);

    if (mTexture == NULL) {
        printf("Failed to open Sprite %s due to %s\n", file, SDL_GetError());
        exit(1);
    }

    int errorValue =
        SDL_QueryTexture(mTexture, nullptr, nullptr, &mWidth, &mHeight);

    if (errorValue != 0) {
        printf("Erro ao query textura\n%s\n", SDL_GetError());
    }

    SetClip(0, 0, mWidth, mHeight);

    mGameObject.mBox.w = mWidth;
    mGameObject.mBox.h = mHeight;
}

void Sprite::SetClip(int x, int y, int w, int h) {
    mClipRect = SDL_Rect{x, y, w, h};
}

void Sprite::Update(float dt) {}

void Sprite::Render() {
    if (mTexture == nullptr) {
        return;
    }

    Rect& rect = mGameObject.mBox;

    SDL_Rect target = rect.toSDL();
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), mTexture, &mClipRect,
                   &target);
}

bool Sprite::Is(std::string type) { return type == "Sprite"; }

bool Sprite::IsOpen() { return mTexture != nullptr; }

Sprite::~Sprite() {
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
    }
}
