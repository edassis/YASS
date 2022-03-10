#include "engine/Collider.h"
#include "engine/Mat.h"

Collider::Collider(GameObject& associated, mat::Vec2 scale, mat::Vec2 offset) : Component(associated) {
    this->scale = scale;
    this->offset = offset;
}

Collider::~Collider() {}

void Collider::SetScale(mat::Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(mat::Vec2 offset) {
    this->offset = offset;
}

void Collider::Update(float dt) {}

void Collider::Render() {}

bool Collider::Is(std::string type) { return type == "Collider"; }