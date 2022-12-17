#pragma once

#include <string>

#include "Texture.h"

class TileSet {
public:
    TileSet(int tileWidth, int tileHeight, std::string file);

    void RenderTile(int32_t index, int x, int y);

    int mTileWidth;
    int mTileHeight;

private:
    // uso de Sprite removido devido ao alto acoplamento de
    // Sprite com GameObject
    Texture& mTexture;

    int mRows;
    int mColumns;
};
