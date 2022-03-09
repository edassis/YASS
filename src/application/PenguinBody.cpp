#include "application/PenguinBody.h"
#include "application/PenguinCannon.h"
#include "engine/Game.h"
#include "engine/InputManager.h"
#include "engine/GameObject.h"
#include "engine/Sprite.h"
#include "engine/State.h"
#include <memory>

// https://stackoverflow.com/questions/38696440/a-standard-way-for-getting-variable-name-at-compile-time
#define NAMEOF(variable) ((void)variable, #variable)
#define W(x) std::cout << NAMEOF(x) << " = " << x << std::endl;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated) {
    speed = {0.0f, 0.0f};
    angle = 0.0f;
    linearSpeed = 0;        // ? How should I use this?
    hp = 10;
    
    auto* rpSprite = new Sprite(associated, "assets/img/penguin.png");
    associated.AddComponent(*rpSprite);

    player = this;
}

PenguinBody::~PenguinBody() {
    player = nullptr;
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
    float friction = 0.8f;
    const float acc = 4.0f;
    const float angleStep = 90.0f;

    auto incSpeed = 0.0f;
    auto incAngle = 0.0f;

    if(inputManager.IsKeyDown(KEYS::A_KEY)) {
        // rotate left
        incAngle += angleStep * dt;
    }
    if(inputManager.IsKeyDown(KEYS::D_KEY)) {
        // rotate right
        incAngle -= angleStep * dt;
    }

    if(inputManager.IsKeyDown(KEYS::W_KEY)) {
        // increase speed
        incSpeed += acc * dt;
    }
    if(inputManager.IsKeyDown(KEYS::S_KEY)) {
        // decrease speed
        incSpeed -= acc * dt;
    }

    angle = std::fmod(angle + incAngle, 360.0f);
    angle += angle + mat::EPS < 0.0f ? 360.0f : 0.0f;
    
    if(std::fabs(incAngle) - mat::EPS > 0.0f) {
        if( auto spSprite = std::dynamic_pointer_cast<Sprite>(associated.GetComponent("Sprite").lock()) ) {
            spSprite->SetAngle(angle);
        } else {
            std::cout << "Warning! PenguinBody::Update() couldn't find the Sprite's pointer." << std::endl;
        }
    }
    
    mat::Vec2 speedVec(incSpeed, 0.0f);
    speedVec = speedVec.Rotated(mat::Deg2Rad(angle));

    speed += speedVec;

    // If not accelerating, should apply friction
    if(std::fabs(incSpeed) < mat::EPS) {
        // if friction greater than speed should use the remanescent speed value as friction
        mat::Vec2 frictionVec(std::min(friction, speed.Length())*dt); 
        frictionVec = frictionVec.Rotated(speed.Angle());
        speed -= frictionVec;
    } 
    
    speed.x = std::max(std::min(speed.x, maxSpeed), -maxSpeed);
    speed.y = std::max(std::min(speed.y, maxSpeed), -maxSpeed);

    auto curPos = associated.box.GetPos();
    associated.box.SetPos(curPos + speed);

    // Die
    // Check if penguin's body died.
    if (hp <= 0) {
        associated.RequestDelete();
    }
}

void PenguinBody::Render() {}

bool PenguinBody::Is(std::string type) { return type == "PenguinBody"; }