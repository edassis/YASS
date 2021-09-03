#include "engine/TileMap.h"
#include <iostream>
#include <fstream>
#include <regex>

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : Component(associated) {
    if(tileSet == nullptr) { // ? What should happen?
        std::cout << "Warning in TileMap(): tileSet variable is nullptr" << std::endl;
    }

    mapWidth = mapHeight = mapDepth = 0;
    this->tileSet = tileSet;

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
        for (rti = iterator_type(token.begin(), token.end(), rgx, 0); rti!=rend; ++rti) {
            int tile = std::stoi(rti->str());
            tile--; // * Indexes starts at -1
            tileMatrix.push_back(tile);
        }
    }
}

void TileMap::SetTileSet(std::string file) {}

int& TileMap::At(int x, int y, int z) {}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {}

void TileMap::Render() {}

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