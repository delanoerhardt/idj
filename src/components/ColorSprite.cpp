#include "components/ColorSprite.h"

#include "Camera.h"
#include "Game.h"

ColorSprite::ColorSprite(GameObject& gameObject, uint8_t r, uint8_t g,
                         uint8_t b, uint8_t a)
    : Component{gameObject}, r{r}, g{g}, b{b}, a{a} {}

void ColorSprite::Render() {
    Rect rect = mGameObject.mBox - Camera::sPos;

    SDL_Rect target = rect.toSDL();

    SDL_SetRenderDrawColor(Game::GetRenderer(), r, g, b, a);

    if (mFill) {
        SDL_RenderFillRect(Game::GetRenderer(), &target);
    } else {
        SDL_RenderDrawRect(Game::GetRenderer(), &target);
    }
}
