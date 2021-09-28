#include "engine/Face.h"
#include "engine/Game.h"
#include "engine/GameObject.h"
#include "engine/Sound.h"
#include "engine/InputManager.h"
#include <iostream>

Face::Face(GameObject& associated) : Component(associated) {
    hitpoints = 30;
    dead = false;
}

void Face::Damage(int damage) {
    if (dead) return;

    hitpoints -= damage <= hitpoints ? damage : hitpoints;

    if(hitpoints == 0) {
        dead = true;

        auto* pt_sprite = dynamic_cast<Sprite*>(associated.GetComponent("Sprite").lock().get());
        associated.RemoveComponent(*pt_sprite);

        auto* pt_cpt = dynamic_cast<Sound*>(associated.GetComponent("Sound").lock().get());
        if(pt_cpt != nullptr) {
            pt_cpt->Play();
        }
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

    if (dead) { // * Assures that Sound::Play() was called.
        auto* sound = dynamic_cast<Sound*>(associated.GetComponent("Sound").lock().get());
        if(sound && !sound->IsPlaying()) {
            associated.RequestDelete();
        }
    }
}

void Face::Render() {}

bool Face::Is(std::string type) { return "Face" == type; }