#include "TileMap.h"

TileMap::TileMap(GameObject& gameObject, const char* filePath, TileSet* tileSet)
    : Component{gameObject},
      mMapWidth{0},
      mMapHeight{0},
      mMapDepth{0},
      mTileSet{tileSet} {
    Open(filePath);
}

void TileMap::Open(const char* filePath) {
    FILE* file = fopen(filePath, "r");

    fscanf(file, " %d, %d, %d, ", &mMapWidth, &mMapHeight, &mMapDepth);

    mMapFloorSize = mMapWidth * mMapHeight;

    mTileMatrix = std::vector<int>(mMapFloorSize * mMapDepth);

    for (int layer = 0; layer < mMapDepth; layer++) {
        for (int y = 0; y < mMapHeight; y++) {
            for (int x = 0; x < mMapWidth; x++) {
                int tileValue = 0;

                fscanf(file, " %d,", &tileValue);

                this->At(x, y, layer) = tileValue - 1;
            }
        }
    }

    fclose(file);
}

void TileMap::SetTileSet(TileSet* tileSet) {
    if (tileSet != nullptr) {
        delete mTileSet;
    }

    mTileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
    return mTileMatrix[z * mMapFloorSize + y * mMapWidth + x];
}

void TileMap::Update(float dt) {}

void TileMap::Render() { RenderLayer(0); }

bool TileMap::Is(std::string type) { return type == "TileMap"; }

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    uint32_t tileWidth = mTileSet->mTileWidth,
             tileHeight = mTileSet->mTileHeight;

    for (int y = 0; y < mMapHeight; y++) {
        for (int x = 0; x < mMapWidth; x++) {
            mTileSet->RenderTile(
                mTileMatrix[layer * mMapFloorSize + y * mMapWidth + x],
                tileWidth * x + mGameObject.mBox.x,
                tileHeight * y + mGameObject.mBox.y);
        }
    }
}
