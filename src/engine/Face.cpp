#include "engine/Face.h"
#include "engine/GameObject.h"
#include "engine/Sound.h"
#include <iostream>

using namespace std;

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

void Face::Update(float dt) {}

void Face::Render() {}

bool Face::Is(string type) { return "Face" == type; }