#include "engine/Face.h"
#include "engine/GameObject.h"
#include "engine/Sound.h"

Face::Face(GameObject &associated) : Component(associated) {
    hitpoints = 30;
}

void Face::Damage(int damage) {
    hitpoints -= damage;

    if(hitpoints <= 0) {
        associated.RequestDelete();

        Sound *cpt = (Sound *) associated.GetComponent("Sound");
        if(cpt != nullptr) {
            cpt->Play();
        }
    }
}

void Face::Update(float dt) {}

void Face::Render() {}