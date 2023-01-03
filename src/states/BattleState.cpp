#include "states/BattleState.h"

#include "Camera.h"
#include "components/Sprite.h"

BattleState::BattleState() {}

void BattleState::Update(float dt) {}

void BattleState::Resume() { Camera::sPos = Vec2{0, 0}; }
