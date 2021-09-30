#include "engine/Bullet.h"
#include "engine/GameObject.h"
#include "engine/Sprite.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string spritePath) : Component(associated) {
    this->damage = damage;
    this->speed.x = speed;
    this->speed = this->speed.Rotated(angle);
    this->distanceLeft = maxDistance;

    auto* pSprite = new Sprite(associated, spritePath);
    associated.AddComponent(*pSprite);
}

int Bullet::GetDamage() {
    return damage;
}

void Bullet::Update(float dt) {
    auto newPos = associated.box.GetPos() + speed * dt;
    associated.box.SetPos(newPos);

    distanceLeft -= (speed * dt).Length();
    if (distanceLeft <= 0.0f) {
        associated.RequestDelete();
    }
}

void Bullet::Render() {}

bool Bullet::Is(std::string type) { return type == "Bullet"; }