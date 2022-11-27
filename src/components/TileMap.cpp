#include "components/TileMap.h"

#include "Camera.h"
#include "Constants.h"

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

void TileMap::Render() {
    float cameraX = Camera::sPos.x, cameraY = Camera::sPos.y;

    RenderLayer(0, cameraX, cameraY);
}

bool TileMap::Is(std::string type) { return type == "TileMap"; }

// Se vou renderizar todas as layers pra causar o parallax, pra que serve esse
// argumento layer?
void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    uint32_t tileWidth = mTileSet->mTileWidth,
             tileHeight = mTileSet->mTileHeight;

    for (int z = layer; z < mMapDepth; z++) {
        int offsetX = (1.0 + (z - layer) * PARALLAX_SPEED) * cameraX;
        int offsetY = (1.0 + (z - layer) * PARALLAX_SPEED) * cameraY;

        for (int y = 0; y < mMapHeight; y++) {
            for (int x = 0; x < mMapWidth; x++) {
                mTileSet->RenderTile(
                    mTileMatrix[z * mMapFloorSize + y * mMapWidth + x],
                    tileWidth * x + mGameObject.mBox.x - offsetX,
                    tileHeight * y + mGameObject.mBox.y - offsetY);
            }
        }
    }
}
