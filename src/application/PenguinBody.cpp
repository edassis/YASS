#include "application/PenguinBody.h"
#include "application/PenguinCannon.h"
#include "engine/Game.h"
#include "engine/InputManager.h"
#include "engine/GameObject.h"
#include "engine/Sprite.h"
#include "engine/State.h"
#include <memory>

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
    const float acc = 3.5f;
    const float angleStep = 30.0f;

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

    mat::Vec2 nSpeed(incSpeed, 0.0f);
    nSpeed = nSpeed.Rotated(mat::Deg2Rad(angle));

    speed += nSpeed;

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