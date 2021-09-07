#include "engine/Face.h"
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
    int mouseX = InputManager::GetInstance().GetMouseX();
    int mouseY = InputManager::GetInstance().GetMouseY();

    auto isClick = InputManager::GetInstance().KeyPress(KEYS::LEFT_MOUSE_BUTTON);
    if (isClick && associated.box.Contains({ float(mouseX), float(mouseY) })) {
        Damage(std::rand() % 10 + 10);
    }
}

void Face::Render() {}

bool Face::Is(std::string type) { return "Face" == type; }