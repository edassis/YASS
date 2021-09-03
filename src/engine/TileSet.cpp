#include "engine/TileSet.h"
#include "engine/GameObject.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) {
    GameObject* go = new GameObject();
    tileset = std::unique_ptr<Sprite>(new Sprite(*go));

    this->tileWitdth = tileWidth;
    this->tileHeight = tileHeight;

    this->rows = tileset->GetHeight() / this->tileHeight;   // * Last tiles can have different sizes (reminder).
    this->columns = tileset->GetWidth() / this->tileWitdth;
}

TileSet::~TileSet() {}

void TileSet::RenderTile(unsigned index, float x, float y) {
    bool isIndexValid = /* index >= 0 && */ index < unsigned(rows*columns);
    if(!isIndexValid) {
        std::cout << "Error! Call of RenderTile() on invalid index." << std::endl; 
        return;
    }

    int qtdLine = index / columns;
    int qtdCol = index - qtdLine;
    int srcX = qtdCol * tileWitdth;
    int srcY = qtdLine *  tileHeight;

    tileset->SetClip(srcX, srcY, tileWitdth, tileHeight);
    tileset->Render(float(x), float(y), float(tileWitdth), float(tileHeight));
}

int TileSet::GetTileWidth() {
    return tileWitdth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}