#include "states/BattleState.h"

#include "Camera.h"
#include "components/ColorSprite.h"
#include "components/Sprite.h"
#include "resources/InputManager.h"

BattleState::BattleState() {
    GameObject *notesSection = new GameObject(Rect{20, 20, 500, 500});
    // Sprite *s = new Sprite{*notesSection, "assets/img/tile_1.png"};
    // notesSection->AddComponent(s);

    ColorSprite *notesSectionSprite =
        new ColorSprite(*notesSection, 255, 255, 255);
    notesSectionSprite->SetFill(true);
    notesSection->AddComponent(notesSectionSprite);

    AddObject(notesSection);
}

void BattleState::Update(float dt) {
    if (InputManager::KeyPressed(SDLK_SPACE)) {
        mPopRequested = true;
    }
}

void BattleState::Resume() { Camera::sPos = Vec2{0, 0}; }
