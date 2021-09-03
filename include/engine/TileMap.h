#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "engine/Component.h"
#include <vector>

class TileSet;

class TileMap : public Component {
    private:
        std::vector<int> tileMatrix;
        TileSet* tileSet;
        int mapWidth;
        int mapHeight;
        int mapDepth;

    public:
        TileMap(GameObject& associated, std::string file, TileSet* tileSet);
        ~TileMap();

        void Load(std::string file);
        void SetTileSet(std::string file);
        int& At(int x, int y, int z = 0);
        void RenderLayer(int layer, int cameraX = 0, int cameraY = 0); 

        /* Component */
        void Render() override;
        void Update(float dt) override;
        bool Is(std::string type) override;

        int GetWidth();
        int GetHeight();
        int GetDepth();

        void Print();
};

#endif