#include "application/PenguinBody.h"
#include "application/PenguinCannon.h"
#include "engine/Game.h"
#include "engine/GameObject.h"
#include "engine/Sprite.h"
#include "engine/State.h"
#include <memory>

PenguinBody::PenguinBody(GameObject& associated) : Component(associated) {
    speed = {0.0f, 0.0f};
    linearSpeed = 80;
    angle = 0.0;
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

void PenguinBody::Update(float dt) {}

void PenguinBody::Render() {}

bool PenguinBody::Is(std::string type) { return "PenguinBody" == type; }
