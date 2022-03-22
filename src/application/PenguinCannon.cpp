#include "application/PenguinCannon.h"
#include "application/PenguinBody.h"
#include "engine/Bullet.h"
#include "engine/Sprite.h"
#include "engine/Collider.h"
#include "engine/InputManager.h"
#include "engine/Game.h"
#include "engine/Camera.h"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated) {
    lastShootTime = 0.f;
    wpBody = penguinBody;

    associated.AddComponent(*new Sprite(associated, "assets/img/cubngun.png"));
    associated.AddComponent(*new Collider(associated));
}

PenguinCannon::~PenguinCannon() {}

void PenguinCannon::Shoot() {
    const auto BULLET_DAMAGE = 3;
    const auto BULLET_SPEED = 300.0f;
    const auto BULLET_MAX_DIST = 3000.0f;

    auto* rpBulletGO = new GameObject();
    auto* rpBullet = new Bullet(*rpBulletGO, associated.angle, BULLET_SPEED,
            BULLET_DAMAGE, BULLET_MAX_DIST, "assets/img/penguinbullet.png", 4, 0.12f, false);

    mat::Vec2 startPos;
    if(auto spBodyGO = wpBody.lock()) {
        // * Assumes that GO always has sprites.
        auto spBodySprite = std::dynamic_pointer_cast<Sprite>(spBodyGO->GetComponent("Sprite").lock());

        startPos.x += (float)spBodySprite->GetWidth();

        startPos = startPos.Rotated(associated.angle);

        startPos += associated.box.Center();
    }
    rpBulletGO->box.Centralize(startPos);

    rpBulletGO->AddComponent(*rpBullet);
    Game::GetInstance().GetState()->AddObject(*rpBulletGO);
}

void PenguinCannon::Update(float dt) {
    auto spBodyGO = wpBody.lock();
    if(!spBodyGO) {
        associated.RequestDelete();
        return;
    }
    
    // * If Timer was a true component I didn't need to do that.
    // * But would handle pointers.
    timer.Update(dt);

    auto& inputManager = InputManager::GetInstance();
    auto& camera = Game::GetInstance().GetState()->GetCamera();
    auto mousePos = mat::Vec2((float)inputManager.GetMouseX(), (float)inputManager.GetMouseY());
    mousePos += camera.GetPos();

    // Centralize cannon over body 
    associated.box.Centralize(spBodyGO->box.Center());
    
    // Points cannon to mouse
    associated.angle = associated.box.Center().AngleToPoint(mousePos);
    // if( auto spSprite = std::dynamic_pointer_cast<Sprite>(associated.GetComponent("Sprite").lock()) ) {
    //     spSprite->SetAngle(associated.angle);
    // } else {
    //     std::cout << "Warning! PenguinCannon::Update() couldn't find the Sprite's pointer." << std::endl;
    // }

    const auto BULLET_SHOOT_INTERVAL = 0.4f;

    if(inputManager.IsKeyDown(KEYS::LEFT_MOUSE_BUTTON)
            && BULLET_SHOOT_INTERVAL < timer.GetTime() - lastShootTime) {
        Shoot();
        lastShootTime = timer.GetTime();
    }
}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(std::string type) { return type == "PenguinCannon"; }

void PenguinCannon::NotifyCollision(const GameObject& other) {
    if(auto spBullet = std::dynamic_pointer_cast<Bullet>(other.GetComponent("Bullet").lock())) {
        // Notify alienCenter to take damage
        if(auto spBody = wpBody.lock()) {
            spBody->NotifyCollision(other);
        } else {
            std::cout << "PenguinCollision::NotifyCollision() unable to access `alienCenter`." << std::endl;
        }
    }
}
