#pragma once

#include <string>

#include "Component.h"
#include "GameObject.h"
#include "Texture.h"

class Sprite : public Component {
public:
    Sprite(GameObject& gameObject);

    Sprite(GameObject& gameObject, std::string file);

    void Open(std::string file);

    void SetClip(int x, int y, int w, int h);

    virtual void Update(float dt);

    virtual void Render();

    virtual bool Is(std::string type);

    bool IsOpen();

    virtual ~Sprite();

    Texture mTexture;

private:
    SDL_Rect mClipRect;
};
