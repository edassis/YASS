#include "engine/TileSet.h"
#include "engine/GameObject.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) /* : go(new GameObject()), sprite(new Sprite(*go)) */ {
    GameObject* go = new GameObject(); // ? Leak!
    sprite = std::unique_ptr<Sprite>(new Sprite(*go, file));

    this->tileWitdth = tileWidth;
    this->tileHeight = tileHeight;

    this->rows = sprite->GetHeight() / this->tileHeight;   // * Last tiles can have different sizes (reminder).
    this->columns = sprite->GetWidth() / this->tileWitdth;
}

TileSet::~TileSet() {}

void TileSet::RenderTile(unsigned index, float x, float y) {
    bool isIndexValid = /* index >= 0 && */ index < unsigned(rows*columns);
    if(!isIndexValid) {
        std::cout << "Error! Call of RenderTile() on invalid index (" << index << ")." << std::endl; 
        // std::cout << rows << ' ' << columns << std::endl;
        return;
    }

    int line = index / columns;
    int col = index - (line*columns);
    int srcX = col * tileWitdth;
    int srcY = line *  tileHeight;

    sprite->SetClip(srcX, srcY, tileWitdth, tileHeight);
    sprite->Render(x, y, float(tileWitdth), float(tileHeight));
}

int TileSet::GetTileWidth() {
    return tileWitdth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}