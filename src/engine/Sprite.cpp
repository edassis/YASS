#include "engine/Sprite.h"

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "engine/SDL_include.h"
#include "engine/Game.h"
#include "engine/Resources.h"
#include "engine/GameObject.h"
#include <iostream>
#include <cmath>

Sprite::Sprite(GameObject& associated) : Component(associated) {
    this->texture = nullptr;
    this->width = 0;
    this->height = 0;
    this->scale = mat::Vec2(1.0f, 1.0f);
    this->angleDeg = 0.0;
}   

Sprite::Sprite(GameObject& associated, std::string file) : Component(associated) {
    this->scale = mat::Vec2(1.0f, 1.0f);
    this->angleDeg = 0.0;
    this->Open(file);
}

Sprite::~Sprite() {}

void Sprite::Open(std::string file) {
    this->texture = Resources::GetInstance().GetImage(file); 

    int _error = SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
    if(_error) {
        std::cout << "Error! Sprite::Open() failed to query texture: " << SDL_GetError() << std::endl;
        return;
    }
    this->SetClip(0, 0, this->width, this->height);

    // * Have to consider the scale.
    associated.box.w = (float)GetWidth();
    associated.box.h = (float)GetHeight();
}

void Sprite::Render() {
    const auto& cameraPos = Game::GetState().GetCamera().GetPos();

    float renderX = associated.box.x - cameraPos.x;
    float renderY = associated.box.y - cameraPos.y;

    Render(renderX, renderY, float(clipRect.w), float(clipRect.h));
}

void Sprite::Render(float x, float y, float w, float h) {   // * Specific of Sprite class
    if(this->texture == nullptr) return;

    SDL_Rect dstRect;
    dstRect.x = (int)round(x);
    dstRect.y = (int)round(y);
    dstRect.w = int(round(w) * scale.x);
    dstRect.h = int(round(h) * scale.y);

    int _error = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, angleDeg, nullptr, SDL_FLIP_NONE);
    if(_error) {
        std::cout << "Error! Sprite::Render() failed to render: " << SDL_GetError() << std::endl;
    }
}

bool Sprite::IsOpen() {
    return (this->texture != nullptr) ? true : false;
}

void Sprite::Update(float dt) {}

bool Sprite::Is(std::string type) { return "Sprite" == type; }

// Sets/Gets --------
void Sprite::SetClip(int x, int y, int w, int h) {  // Origin
    this->clipRect.x = x;
    this->clipRect.y = y;
    this->clipRect.w = w;
    this->clipRect.h = h;
}


void Sprite::SetScale(mat::Vec2& scale) {
    scale.x = (scale.x < 0.01f) ? 1.0f : scale.x;
    scale.y = (scale.y < 0.01f) ? 1.0f : scale.y;

    // * Update parent GameObject's witdh/height keeping him centralized in the same position.
    auto centerPoint = associated.box.Center();
    associated.box.w = float(GetWidth());
    associated.box.h = float(GetHeight());
    associated.box.Centralize(centerPoint);

    this->scale = scale;
}

void Sprite::SetScale(float x, float y) {
    x = (x < 0.01f) ? 1.0f : x;
    y = (y < 0.01f) ? 1.0f : y;

    this->scale.x = x;
    this->scale.y = y;
}

int Sprite::GetWidth() {
    return int((float)this->width * this->scale.x);
}

int Sprite::GetHeight() {
    return int((float)this->height * this->scale.y);
}

mat::Vec2 Sprite::GetScale() {
    return scale;
}

double Sprite::GetAngle() {
    return angleDeg;
}

void Sprite::SetAngle(const double& deg) {
    angleDeg = deg;
}