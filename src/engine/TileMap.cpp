#include "engine/TileMap.h"
#include "engine/Game.h"
#include "engine/TileSet.h"
#include "engine/GameObject.h"
#include <iostream>
#include <fstream>
#include <regex>

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : Component(associated), tileSet(tileSet) {
    if(tileSet == nullptr) { // ? What should happen?
        std::cout << "Warning! TileMap::TileMap(): tileSet variable is nullptr" << std::endl;
    }

    mapWidth = mapHeight = mapDepth = 0;

    Load(file);
}

TileMap::~TileMap() {}

void TileMap::Load(std::string file) {
    std::ifstream myFile(file, std::ios::in);
    if(!myFile.is_open()) {
        std::cout << "Error! TileMap::Load() failed to open file (" << file << ")." << std::endl;
        return;
    }

    // https://www.cplusplus.com/reference/regex/regex_token_iterator/operator=/
    // https://stackoverflow.com/questions/16749069/c-split-string-by-regex
    typedef std::regex_token_iterator<std::string::iterator> iterator_type;
    iterator_type rti, rend;

    std::string token;
    std::regex rgx("[0-9]+");
    std::getline(myFile, token); // w,h,z
    
    rti = iterator_type(token.begin(), token.end(), rgx, 0);
    mapWidth = std::stoi(rti->str());
    
    rti++;
    mapHeight = std::stoi(rti->str());

    rti++;
    mapDepth = std::stoi(rti->str());

    while(std::getline(myFile, token)) {
        for (rti = iterator_type(token.begin(), token.end(), rgx, 0); rti!=rend; rti++) {
            int tile = std::stoi(rti->str());
            tile--; // * Indexes starts at -1
            tileMatrix.push_back(tile);
        }
    }
    
    // ? Needed:
    associated.box.w = float(mapWidth * tileSet->GetTileWidth());
    associated.box.h = float(mapHeight * tileSet->GetTileHeight());
}

// https://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/
void TileMap::SetTileSet(std::unique_ptr<TileSet> tileSet) {
    this->tileSet = std::move(tileSet);
}

int& TileMap::At(int x, int y, int z) {
    if(x >= mapWidth && y >= mapHeight && z >= mapDepth) {
        std::cout << "Error! TileMap::At() invalid parameters." << std::endl;
        x = y = z = 0;  // * Takes first tile in case coordinates are invalid.
    }

    int idx = x + (y*mapWidth) + (z*mapWidth*mapHeight);

    return tileMatrix[idx];
}

// ? Camera should be a Rect? Should have width and height I think.
void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    for(int y = 0; y < mapHeight; y++) {
        for(int x = 0; x < mapWidth; x++) {
            float dstX = float(x*tileSet->GetTileWidth()-cameraX);
            float dstY = float(y*tileSet->GetTileHeight()-cameraY);

            int tile = At(x, y, layer);
            
            if(tile >= 0) { // -1 = empty tile
                tileSet->RenderTile(unsigned(tile), dstX, dstY);
            }
        }
    }
}

void TileMap::Render() {
    const auto& cameraPos = Game::GetState().GetCamera().pos;
    
    for(int layer = 0; layer < mapDepth; layer++) {
        RenderLayer(layer, int(cameraPos.x) >> layer, int(cameraPos.y) >> layer);   // * Simple parallax effect.
    }
}

void TileMap::Update(float dt) {}

bool TileMap::Is(std::string type) { return "TileMap" == type; }

int TileMap::GetWidth() { return mapWidth; }

int TileMap::GetHeight() { return mapHeight; }

int TileMap::GetDepth() { return mapDepth; }

void TileMap::Print() {
    std::cout << "Width: " << GetWidth() << std::endl;
    std::cout << "Height: " << GetHeight() << std::endl;
    std::cout << "Depth: " << GetDepth() << std::endl;

    int n = (int)tileMatrix.size();
    std::cout << "Tiles: " << n << std::endl;
    int dep = 1;
    for(int i=0; i<n; i++) {
        if(i % (mapWidth*mapHeight) == 0) {
            std::cout << "\nDepth -- " << dep << std::endl;
            dep++;
        }

        std::cout << tileMatrix[i] << ' ';
        
        if((i+1) % mapWidth == 0) {
            std::cout << std::endl;
        }
    }
}