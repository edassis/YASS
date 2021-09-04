#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "engine/Component.h"
#include <memory>
#include <vector>

class TileSet;

class TileMap : public Component {
    private:
        // Tiles content
        std::vector<int> tileMatrix;
        // Tiles spritesheet
        std::unique_ptr<TileSet> tileSet;
        // Tiles per line
        int mapWidth;
        // Tiles per column
        int mapHeight;
        // Tiles per layer
        int mapDepth;

    public:
        TileMap(GameObject& associated, std::string file, TileSet* tileSet);
        ~TileMap();

        void Load(std::string file);
        void SetTileSet(std::unique_ptr<TileSet> tileSet);
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