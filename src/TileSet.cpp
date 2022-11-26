#include "TileSet.h"

#include "Game.h"
#include "Resources.h"

// uso de Sprite removido devido ao alto acoplamento de
// Sprite com GameObject

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) {
    mTexture = Resources::GetImage(file);

    mTileWidth = tileWidth;
    mTileHeight = tileHeight;

    mColumns = mTexture.width / mTileWidth;
    mRows = mTexture.height / mTileHeight;
}

void TileSet::RenderTile(int32_t index, int x, int y) {
    if (index < 0 || index >= mTileWidth * mTileHeight) {
        return;
    }

    SDL_Rect srcRect{(index % mColumns) * mTileWidth,
                     (index / mColumns) * mTileHeight, mTileWidth, mTileHeight};

    SDL_Rect destRect{x, y, mTileWidth, mTileHeight};

    SDL_RenderCopy(Game::GetInstance().GetRenderer(), mTexture.sdlTexture,
                   &srcRect, &destRect);
}
