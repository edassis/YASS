#include "engine/Sprite.h"

#define INCLUDE_SDL_IMAGE
#include "engine/SDL_include.h"
#include "engine/Game.h"
#include <iostream>

using std::cout;
using std::endl;

Sprite::Sprite() {
    this->texture = nullptr;
}

Sprite::Sprite(string file) {
    this->texture = nullptr;
    this->Open(file);
}

Sprite::~Sprite() {
    if(this->texture != nullptr) {
        SDL_DestroyTexture(this->texture);
    }
}

void Sprite::Open(string file) {
    if(this->texture != nullptr) {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }

    this->texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if(this->texture == nullptr) {
        cout << "Failed to load texture: " << IMG_GetError() << endl;
        return;
    }

    int _error = SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
    if(_error) {
        cout << "Failed to query texture: " << SDL_GetError() << endl;
        return;
    }
    this->SetClip(0, 0, this->width, this->height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    this->clipRect.x = x;
    this->clipRect.y = y;
    this->clipRect.w = w;
    this->clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    if(this->texture == nullptr) return;

    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = this->clipRect.w;
    dstRect.h = this->clipRect.h;

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