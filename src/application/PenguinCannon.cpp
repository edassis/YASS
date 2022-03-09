#include "application/PenguinCannon.h"
#include "application/PenguinBody.h"
#include "engine/Bullet.h"
#include "engine/Sprite.h"
#include "engine/InputManager.h"
#include "engine/Game.h"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated) {
    angle = 0;
    wpBody = penguinBody;

    auto* rpSprite = new Sprite(associated, "assets/img/cubngun.png");
    associated.AddComponent(*rpSprite);
}

PenguinCannon::~PenguinCannon() {}

void PenguinCannon::Shoot() {
    const auto BULLET_DAMAGE = 3;
    const auto BULLET_SPEED = 300.0f;
    const auto BULLET_MAX_DIST = 3000.0f;
    
    auto* rpBulletGO = new GameObject();
    auto* rpBullet = new Bullet(*rpBulletGO, angle, BULLET_SPEED, BULLET_DAMAGE, BULLET_MAX_DIST, "assets/img/penguinbullet.png", 4, 0.12f);

    mat::Vec2 startPos = associated.box.Center();
    if(auto spBodyGO = wpBody.lock()) {
        // * Assumes that GO always has sprites.
        auto spBodySprite = std::dynamic_pointer_cast<Sprite>(spBodyGO->GetComponent("Sprite").lock());
        startPos.x += (float)spBodySprite->GetWidth();
        startPos.y += (float)spBodySprite->GetHeight()/2;
    }
    rpBulletGO->box.Centralize(startPos);

    rpBulletGO->AddComponent(*rpBullet);
    Game::GetState().AddObject(*rpBulletGO);
}

void PenguinCannon::Update(float dt) {
    auto spBodyGO = wpBody.lock();
    if(!spBodyGO) {
        associated.RequestDelete();
        return;
    }

    auto& inputManager = InputManager::GetInstance();
    auto& camera = Game::GetState().GetCamera();
    auto mousePos = mat::Vec2(inputManager.GetMouseX(), inputManager.GetMouseY());
    mousePos += camera.GetPos();

    // Centralize cannon over body 
    associated.box.Centralize(spBodyGO->box.Center());
    
    // Points cannon to mouse
    angle = mat::Rad2Deg(associated.box.Center().AngleToPoint(mousePos));
    if( auto spSprite = std::dynamic_pointer_cast<Sprite>(associated.GetComponent("Sprite").lock()) ) {
        spSprite->SetAngle(angle);
    } else {
        std::cout << "Warning! PenguinCannon::Update() couldn't find the Sprite's pointer." << std::endl;
    }

    if(inputManager.KeyPress(KEYS::LEFT_MOUSE_BUTTON)) {
        Shoot();
    }
}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(std::string type) { return type == "PenguinCannon"; }