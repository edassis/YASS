#include "engine/Sprite.h"

#define INCLUDE_SDL_IMAGE
#include "engine/SDL_include.h"
#include "engine/Game.h"
#include "engine/Resources.h"
#include "engine/GameObject.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

Sprite::Sprite(GameObject& associated) : Component(associated) {
    this->texture = nullptr;
    this->width = 0;
    this->height = 0;
}   

Sprite::Sprite(GameObject& associated, string file) : Component(associated) {
    this->texture = nullptr;
    this->Open(file);
}

Sprite::~Sprite() {}

void Sprite::Open(string file) {
    this->texture = Resources::GetInstance().GetImage(file); 

    int _error = SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
    if(_error) {
        cout << "Error! Sprite::Open() failed to query texture: " << SDL_GetError() << endl;
        return;
    }
    this->SetClip(0, 0, this->width, this->height);

    associated.box.w = (float)this->width;
    associated.box.h = (float)this->height;
}

void Sprite::SetClip(int x, int y, int w, int h) {  // origin
    this->clipRect.x = x;
    this->clipRect.y = y;
    this->clipRect.w = w;
    this->clipRect.h = h;
}

void Sprite::Render() {
    Render(associated.box.x, associated.box.y, associated.box.w, associated.box.h);
}

void Sprite::Render(float x, float y, float w, float h) {   // * Specific of Sprite class
    if(this->texture == nullptr) return;

    SDL_Rect dstRect;
    dstRect.x = (int)round(x);
    dstRect.y = (int)round(y);
    dstRect.w = (int)round(w);
    dstRect.h = (int)round(h);

    int _error = SDL_RenderCopy(Game::GetInstance().GetRenderer(), this->texture, &this->clipRect, &dstRect);
    if(_error) {
        cout << "Failed to render: " << SDL_GetError() << endl;
    }
}

int Sprite::GetWidth() {
    return this->width;
}

int Sprite::GetHeight() {
    return this->height;
}

bool Sprite::IsOpen() {
    return (this->texture != nullptr) ? true : false;
}

void Sprite::Update(float dt) {}

bool Sprite::Is(string type) { return "Sprite" == type; }