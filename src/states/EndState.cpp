#include "states/EndState.h"

#include "Camera.h"
#include "Constants.h"
#include "Game.h"
#include "components/Sprite.h"
#include "components/Text.h"
#include "resources/GameData.h"
#include "resources/InputManager.h"
#include "states/TitleState.h"
#include "util/Logger.h"

EndState::EndState() {
    std::string spriteFile =
        GameData::playerVictory ? "assets/img/win.jpg" : "assets/img/lose.jpg";
    std::string musicFile = GameData::playerVictory
                                ? "assets/audio/endStateWin.ogg"
                                : "assets/audio/endStateLose.ogg";

    mMusic = new Music{musicFile};
    mMusic->Play();

    GameObject *titleSplashObject = new GameObject();
    Sprite *titleSprite = new Sprite(*titleSplashObject, spriteFile);
    titleSplashObject->AddComponent(titleSprite);

    AddObject(titleSplashObject);

    GameObject *textObject = new GameObject(0, 0);
    Text *titleText = new Text(
        *textObject, "ESPACO  para  jogar  novamente ou ESC  para  sair");

    textObject->CenterAt(Vec2{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 200})
        ->AddComponent(titleText);

    AddObject(textObject);
}

void EndState::Update(float dt) {
    if (InputManager::QuitRequested() ||
        InputManager::KeyPressed(SDLK_ESCAPE)) {
        mQuitRequested = true;
    } else if (InputManager::KeyPressed(SDLK_SPACE)) {
        mPopRequested = true;
        Game::Push(new TitleState());
    }
}

void EndState::Resume() { Camera::sPos = Vec2{0, 0}; }