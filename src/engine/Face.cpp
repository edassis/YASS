#include "engine/Face.h"
#include "engine/Game.h"
#include "engine/GameObject.h"
#include "engine/Sound.h"
#include "engine/InputManager.h"
#include <iostream>

Face::Face(GameObject& associated) : Component(associated) {
    hitpoints = 30;
}

void Face::Damage(int damage) {
    hitpoints -= damage;

    if(hitpoints <= 0) {
        associated.RequestDelete();
    }

    Sound* cpt = (Sound *) associated.GetComponent("Sound").get();
    if(cpt != nullptr) {
        cpt->Play();
    }
}

void Face::Update(float dt) {
    const auto& cameraPos = Game::GetState().GetCamera().pos;
    float mouseX = (float) InputManager::GetInstance().GetMouseX();
    float mouseY = (float) InputManager::GetInstance().GetMouseY();

    float posX = mouseX + cameraPos.x;
    float posY = mouseY + cameraPos.y;

    auto isClick = InputManager::GetInstance().KeyPress(KEYS::LEFT_MOUSE_BUTTON);
    if (isClick && associated.box.Contains( {posX, posY} )) {
        Damage(std::rand() % 10 + 10);
    }
}

void Face::Render() {}

bool Face::Is(std::string type) { return "Face" == type; }