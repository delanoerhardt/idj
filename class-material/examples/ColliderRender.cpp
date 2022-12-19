
// Adicione o trecho abaixo no começo do seu Collider.cpp,
// logo após os seus includes e antes de qualquer função.

#ifdef DEBUG
#include <SDL2/SDL.h>

#include "Camera.h"
#include "Game.h"
#endif  // DEBUG

// Copie o conteúdo dessa função para dentro da sua e adapte o nome das funções
// para as suas. Funções usadas:
// Rect::GetCenter()				- Retorna um Vec2 no centro do
// Rect Vec2::operator-( const Vec2& )	- Subtrai dois Vec2 Vec2::Rotate( float
// rad )		- Rotaciona um Vec2 pelo ângulo em radianos passado
void Collider::Render() {
#ifdef DEBUG
    Vec2 center(mGameObject.mBox.Center());
    SDL_Point points[5];

    Vec2 point =
        (Vec2(mGameObject.mBox.x, mGameObject.mBox.y) - center).Rotate(mAngle) +
        center - Camera::sPos;
    points[0] = {(int)point.x, (int)point.y};
    points[4] = {(int)point.x, (int)point.y};

    point = (Vec2(mGameObject.mBox.x + mGameObject.mBox.w, mGameObject.mBox.y) -
             center)
                .Rotate(mAngle) +
            center - Camera::sPos;
    points[1] = {(int)point.x, (int)point.y};

    point = (Vec2(mGameObject.mBox.x + mGameObject.mBox.w,
                  mGameObject.mBox.y + mGameObject.mBox.h) -
             center)
                .Rotate(mAngle) +
            center - Camera::sPos;
    points[2] = {(int)point.x, (int)point.y};

    point = (Vec2(mGameObject.mBox.x, mGameObject.mBox.y + mGameObject.mBox.h) -
             center)
                .Rotate(mAngle) +
            center - Camera::sPos;
    points[3] = {(int)point.x, (int)point.y};

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0,
                           SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif  // DEBUG
}