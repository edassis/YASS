#include "application/PenguinCannon.h"
#include "engine/Sprite.h"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated) {
    angle = 0;
    wpBody = penguinBody;

    auto* rpSprite = new Sprite(associated, "assets/img/cubngun.png");
    associated.AddComponent(*rpSprite);
}

PenguinCannon::~PenguinCannon() {}

void PenguinCannon::Shoot() {

}

void PenguinCannon::Update(float dt) {

}

void PenguinCannon::Render() {

}

bool PenguinCannon::Is(std::string type) { return type == "PenguinCannon"; }