#include "engine/TileSet.h"
#include "engine/GameObject.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) {
    GameObject* go = new GameObject();
    tileset = std::unique_ptr<Sprite>(new Sprite(*go));
}