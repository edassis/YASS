#include "application/Minion.h"
#include "engine/GameObject.h"
#include "engine/Sprite.h"
#include "engine/Mat.h"
#include "engine/Bullet.h"
#include "engine/Game.h"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(alienCenter) {
    this->arcDeg = arcOffsetDeg;

    auto* sprite = new Sprite(associated, "assets/img/minion.png");
    float scale = mat::randf() * 1.5f;
    scale = std::max(1.0f, scale);
    sprite->SetScale(scale, scale);

    associated.AddComponent(*sprite);
}

void Minion::Update(float dt) {
    const float ROTATIONAL_VEL = 60.0f;   // degrees/s
    const auto PIVOT_DIST = mat::Vec2(200.0f, 0.0f);   // Distance from pivot of rotation.
    
    if(auto wpPivot = alienCenter.lock()) {
        arcDeg += std::fmod(ROTATIONAL_VEL * dt, 360.0f);
        auto pos = PIVOT_DIST.Rotated(mat::Deg2Rad(arcDeg));
        pos += wpPivot->box.Center();

        associated.box.Centralize(pos);

        auto angle = wpPivot->box.Center().AngleToPoint(associated.box.Center());
        
        if( auto spSprite = std::dynamic_pointer_cast<Sprite>(associated.GetComponent("Sprite").lock()) )  {
            spSprite->SetAngle(mat::Rad2Deg(angle));  // * Considers normal vector poiting downwards.
        } else {
            std::cout << "Warning! Minion::Update() couldn't find the Sprite's pointer." << std::endl;
        }
    }
    else {
        associated.RequestDelete();
    }
}

void Minion::Render() {}

bool Minion::Is(std::string type) { return type == "Minion"; }

void Minion::Shoot(mat::Vec2 target) {
    const auto BULLET_SPEED = 350.0f;
    const auto BULLET_DAMAGE = 10.0f;
    const auto BULLET_MAX_DIST = 3000.0f;

    auto angle = associated.box.Center().AngleToPoint(target);

    auto* pBulletGO = new GameObject();
    auto* pBullet = new Bullet(*pBulletGO, angle, BULLET_SPEED, BULLET_DAMAGE, BULLET_MAX_DIST, "assets/img/minionbullet1.png");

    pBulletGO->box.Centralize(associated.box);

    pBulletGO->AddComponent(*pBullet);

    Game::GetState().AddObject(*pBulletGO);
}