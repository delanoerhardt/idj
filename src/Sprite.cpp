#include "Sprite.h"

#include "Camera.h"
#include "Game.h"
#include "Resources.h"

Sprite::Sprite(GameObject& gameObject)
    : Component{gameObject}, mTexture{nullptr, 0, 0} {}

Sprite::Sprite(GameObject& gameObject, std::string file) : Sprite{gameObject} {
    Open(file);
}

void Sprite::Open(std::string file) {
    mTexture = Resources::GetImage(file);

    SetClip(0, 0, mTexture.width, mTexture.height);

    mGameObject.mBox.w = mTexture.width;
    mGameObject.mBox.h = mTexture.height;
}

void Sprite::SetClip(int x, int y, int w, int h) {
    mClipRect = SDL_Rect{x, y, w, h};
}

void Sprite::Update(float dt) {}

void Sprite::Render() {
    if (mTexture.sdlTexture == nullptr) {
        return;
    }

    Vec2 cameraPos = Camera::sPos;

    Rect rect = mGameObject.mBox - cameraPos;

    SDL_Rect target = rect.toSDL();
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), mTexture.sdlTexture,
                   &mClipRect, &target);
}

bool Sprite::Is(std::string type) { return type == "Sprite"; }

bool Sprite::IsOpen() { return mTexture.sdlTexture != nullptr; }

Sprite::~Sprite() {}
