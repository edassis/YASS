#include "application/PenguinBody.h"
#include "application/PenguinCannon.h"
#include "engine/Game.h"
#include "engine/InputManager.h"
#include "engine/GameObject.h"
#include "engine/Sprite.h"
#include "engine/Collider.h"
#include "engine/Bullet.h"
#include "engine/State.h"
#include <memory>

// https://stackoverflow.com/questions/38696440/a-standard-way-for-getting-variable-name-at-compile-time
#define NAMEOF(variable) ((void)variable, #variable)
#define W(x) std::cout << NAMEOF(x) << " = " << x << std::endl;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated) {
    speed = {0.0f, 0.0f};
    // angle = 0.0f;
    linearSpeed = 0;        // ? How should I use this?
    hp = 10;
    
    auto* rpSprite = new Sprite(associated, "assets/img/penguin.png");
    auto* rpCollider = new Collider(associated);
    associated.AddComponent(*rpSprite);
    associated.AddComponent(*rpCollider);

    // player = this;
}

PenguinBody::~PenguinBody() {
    // player = nullptr;
}

void PenguinBody::Start() {
    auto wpBody = Game::GetState().GetObjectPtr(associated);

    auto* rpCannonGO = new GameObject();
    auto* rpCannon = new PenguinCannon(*rpCannonGO, wpBody);
    rpCannonGO->AddComponent(*rpCannon);

    this->wpCannon = Game::GetState().AddObject(*rpCannonGO);
}

void PenguinBody::Update(float dt) {
    auto& inputManager = InputManager::GetInstance();
    
    const float maxSpeed = 14.0f;
    const float friction = 1.0f;
    const float acc = 4.0f;
    const float angleStep = mat::Deg2Rad(90.0f);

    auto incSpeed = 0.0f;
    auto incAngle = 0.0f;

    if(inputManager.IsKeyDown(KEYS::A_KEY)) {
        // rotate left
        incAngle -= angleStep * dt;
    }
    if(inputManager.IsKeyDown(KEYS::D_KEY)) {
        // rotate right
        incAngle += angleStep * dt;
    }

    if(inputManager.IsKeyDown(KEYS::W_KEY)) {
        // increase speed
        incSpeed += acc * dt;
    }
    if(inputManager.IsKeyDown(KEYS::S_KEY)) {
        // decrease speed
        incSpeed -= acc * dt;
    }
    
    associated.angle += incAngle;
    associated.angle += associated.angle + mat::EPS < 0.0f ? 2*mat::PI : 0.0f;
    associated.angle = std::fmod(associated.angle, 2*mat::PI);

    // if(std::fabs(incAngle) - mat::EPS > 0.0f) { // Check if angle changed.
    //     if( auto spSprite = std::dynamic_pointer_cast<Sprite>(associated.GetComponent("Sprite").lock()) ) {
    //         spSprite->SetAngle(associated.angle);
    //     } else {
    //         std::cout << "Warning! PenguinBody::Update() couldn't find the Sprite's pointer." << std::endl;
    //     }
    // }
    
    mat::Vec2 speedIncVec(incSpeed, 0.0f);
    speedIncVec = speedIncVec.Rotated(associated.angle);

    speed += speedIncVec;

    // If not accelerating, should apply friction
    if(std::fabs(incSpeed) < mat::EPS) {
        // if friction greater than speed should use the remanescent speed value as friction
        mat::Vec2 frictionVec(std::min(friction, speed.Length())*dt); 
        frictionVec = frictionVec.Rotated(speed.Angle());
        speed -= frictionVec;
    } 
    
    auto dest = associated.box.GetPos() + speed;

    speed.x = std::max(std::min(speed.x, maxSpeed), -maxSpeed);
    speed.y = std::max(std::min(speed.y, maxSpeed), -maxSpeed);

    associated.box.SetPos(dest);
}

void PenguinBody::Render() {}

bool PenguinBody::Is(std::string type) { return type == "PenguinBody"; }

void PenguinBody::NotifyCollision(const GameObject& other) {
    auto spBullet = std::dynamic_pointer_cast<Bullet>(other.GetComponent("Bullet").lock());
    if(!spBullet) return;

    auto spPlayer = Game::GetState().GetPlayerPointer().lock();
    
    // Take damage
    // If Penguin shoot with IsTargetPlayer off it's possible to cause a self injure xD 
    if((spBullet->IsTargetPlayer() && spPlayer.get() == &associated)
            || !spBullet->IsTargetPlayer()) {
        hp -= spBullet->GetDamage();
    }

    if(hp <= 0) {
        associated.RequestDelete();
        if(spPlayer.get() == &associated) Game::GetState().GetCamera().Unfollow();
    }
}