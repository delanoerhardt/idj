#include "states/TitleState.h"

#include "Camera.h"
#include "Constants.h"
#include "Game.h"
#include "components/Sprite.h"
#include "components/Text.h"
#include "resources/InputManager.h"
#include "states/StageState.h"

TitleState::TitleState() {
    GameObject *titleSplashObject = new GameObject();
    Sprite *titleSprite =
        new Sprite(*titleSplashObject, "assets/img/title.jpg");
    titleSplashObject->AddComponent(titleSprite);

    AddObject(titleSplashObject);

    GameObject *titleTextObject = new GameObject();
    Text *titleText = new Text(
        *titleTextObject, "Aperte  ESPACO  para  comecar ou ESC para sair!");

    titleTextObject->CenterAt(Vec2{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 200})
        ->AddComponent(titleText);

    AddObject(titleTextObject);
}

void TitleState::Update(float dt) {
    if (InputManager::QuitRequested() ||
        InputManager::KeyPressed(SDLK_ESCAPE)) {
        mQuitRequested = true;
    }

    if (InputManager::KeyPressed(SDLK_SPACE)) {
        Game::Push(new StageState());
    }
}

void TitleState::Resume() { Camera::sPos = Vec2{0, 0}; }