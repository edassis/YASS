#include "engine/Bullet.h"
#include "engine/GameObject.h"
#include "engine/Sprite.h"
#include "engine/Collider.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string spritePath, int frameCount, float frameTime) : Component(associated) {
    this->damage = damage;
    this->speed.x = speed;
    this->speed = this->speed.Rotated(angle);
    this->distanceLeft = maxDistance;

    auto* rpSprite = new Sprite(associated, spritePath, frameCount, frameTime);
    auto* rpCollider = new Collider(associated);
    associated.AddComponent(*rpSprite);
    associated.AddComponent(*rpCollider);

    associated.angle = angle; 
    // * Update angle.
    if (auto spSprite = std::dynamic_pointer_cast<Sprite>(associated.GetComponent("Sprite").lock()) ) {
        spSprite->SetScale(2.0f, 2.0f);
        // spSprite->SetAngle(angle);
    } else {
        std::cout << "Warning! Bullet::Update() couldn't find the Sprite's pointer." << std::endl;
    }
}

int Bullet::GetDamage() {
    return damage;
}

void Bullet::Update(float dt) {
    // * Update position.
    auto newPos = associated.box.GetPos() + speed * dt;
    associated.box.SetPos(newPos);

    distanceLeft -= (speed * dt).Length();
    if (distanceLeft <= 0.0f) {
        associated.RequestDelete();
    }
}

void Bullet::Render() {}

bool Bullet::Is(std::string type) { return type == "Bullet"; }

void Bullet::NotifyCollision(const GameObject& other) {
    if(!other.GetComponent("Bullet").lock()) {
        // If not bullet, request deletion
        associated.RequestDelete();
    }
}