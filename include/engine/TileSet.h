#ifndef __TILESET_H__
#define __TILESET_H__

#include "engine/Sprite.h"
#include <iostream>
#include <memory>

class TileSet {
    private:
        std::unique_ptr<Sprite> tileset;
        int rows;
        int columns;
        int tileWitdth;
        int tileHeight;
    public:
        TileSet(int tileWitdth, int tileHeight, std::string file);
        ~TileSet();

        void RenderTile(unsigned index, float x, float y);
        int GetTileWidth();
        int GetTileHeight();
};

#endif