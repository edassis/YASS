#include "engine/Sprite.h"

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "engine/SDL_include.h"
#include "engine/Game.h"
#include "engine/Resources.h"
#include "engine/GameObject.h"
#include "engine/Camera.h"
#include <iostream>
#include <cmath>
#include <limits>

Sprite::Sprite(GameObject& associated) : Component(associated) {
    this->frameCurrent = 0;
    this->frameCount = 1;
    this->frameTime = std::numeric_limits<decltype(this->frameTime)>::max();
    this->timeElapsed = 0.0f;
    this->lifeSpan = std::numeric_limits<decltype(this->lifeSpan)>::max();

    this->texture = nullptr;
    
    this->width = 0;
    this->height = 0;
    this->scale = mat::Vec2(1.0f, 1.0f);
    // this->angleDeg = 0.0f;
}   

Sprite::Sprite(GameObject& associated, std::string file, int frameCount, float frameTime, float lifeSpan) : Component(associated) {
    this->frameCurrent = 0;
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    this->timeElapsed = 0.0f;
    this->lifeSpan = lifeSpan;

    this->scale = mat::Vec2(1.0f, 1.0f);
    // this->angleDeg = 0.0f;

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
    
    // Define sprite's width as his frame width.
    width = width/frameCount;
    
    this->SetClip(0, 0, GetWidth(), GetHeight());

    UpdateBoxSize();
}

void Sprite::Render() {
    const auto& cameraPos = Game::GetInstance().GetState()->GetCamera().GetPos();

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

    int _error = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),
            texture, &clipRect, &dstRect, mat::Rad2Deg(associated.angle), nullptr, SDL_FLIP_NONE);
    if(_error) {
        std::cout << "Error! Sprite::Render() failed to render: " << SDL_GetError() << std::endl;
    }
}

bool Sprite::IsOpen() {
    return (this->texture != nullptr) ? true : false;
}

void Sprite::Update(float dt) {
    // ? Should store total running time? (Is telling the current frame time).
    timeElapsed += dt;
    age.Update(dt);
    
    if(frameTime < timeElapsed) {
        SetFrame((frameCurrent+1)%frameCount);
        timeElapsed = 0.0f;
    }

    if(age.GetTime() > lifeSpan) {
        // too old 
        associated.RequestDelete();
    }
}

bool Sprite::Is(std::string type) { return "Sprite" == type; }

void Sprite::UpdateBoxSize() {
    // Collision box may respect frame size.
    this->associated.box.w = float(GetWidth());
    this->associated.box.h = float(GetHeight());
}

// Sets/Gets --------
void Sprite::SetClip(int x, int y, int w, int h) {  // Origin
    this->clipRect.x = x;
    this->clipRect.y = y;
    this->clipRect.w = w;
    this->clipRect.h = h;
}

void Sprite::SetScale(mat::Vec2& scale) {
    SetScale(scale.x, scale.y);
}

void Sprite::SetScale(float x, float y) {
    // x = (x < 0.01f) ? 1.0f : x;
    // y = (y < 0.01f) ? 1.0f : y;
    this->scale.x = x;
    this->scale.y = y;
    
    // * Update parent GameObject's width/height keeping him centralized in the same position.
    auto centerPoint = associated.box.Center();
    UpdateBoxSize();
    associated.box.Centralize(centerPoint);
}

// void Sprite::SetAngle(const float& rad) {
//     angleDeg = mat::Rad2Deg(rad);
// }

void Sprite::SetFrame(int frame) {
    if(frame < 0 || frame >= frameCount) {
        std::cout << "Error! Sprite::SetFrame() called with out of bonds frame value." <<  std::endl;
    }
    this->frameCurrent = frame;

    auto frame_posx = frameCurrent*clipRect.w;

    SetClip(frame_posx, clipRect.y, clipRect.w, clipRect.h);
}

void Sprite::SetFrameCount(int frameCount) {
    if(frameCount < 0) {
        std::cout << "Error! Sprite::SetFrameCount() called with negative frameCount." <<  std::endl;
    }
 
    this->frameCount = frameCount;
    SetFrame(0);
    // Collision box must be adjusted 
    UpdateBoxSize();
}

void Sprite::SetFrameTime(float frameTime) {
    this->frameTime = frameTime;
}

int Sprite::GetWidth() {
    return (int)floor((float)this->width * GetScale().x);
}

int Sprite::GetHeight() {
    return (int)floor((float)this->height * GetScale().y);
}

mat::Vec2 Sprite::GetScale() {
    return scale;
}

// float Sprite::GetAngle() {
//     return mat::Deg2Rad(angleDeg);
// }
