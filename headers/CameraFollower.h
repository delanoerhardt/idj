#pragma once

#include "Camera.h"
#include "Component.h"

class CameraFollower : public Component {
public:
    CameraFollower(GameObject& gameObject) : Component{gameObject} {}

    virtual void Update(float dt) {
        Vec2& cameraPosition = Camera::sPos;
        mGameObject.mBox.x = cameraPosition.x;
        mGameObject.mBox.y = cameraPosition.y;
    }

    virtual void Render() {}

    virtual bool Is(std::string type) { return type == "CameraFollower"; }
};