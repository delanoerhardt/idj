#pragma once

#include "Component.h"
#include "TileSet.h"

class TileMap : public Component {
public:
    TileMap(GameObject& gameObject, const char* filePath, TileSet* tileSet);

    void Open(const char* filePath);

    void SetTileSet(TileSet* tileSet);

    inline int& At(int x, int y, int z = 0);

    virtual void Update(float dt);

    virtual void Render();

    virtual bool Is(std::string type);

    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

    int mMapWidth;
    int mMapHeight;
    int mMapDepth;

    int mMapFloorSize;

private:
    std::vector<int> mTileMatrix;
    TileSet* mTileSet;
};
