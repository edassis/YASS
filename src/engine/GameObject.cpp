#include "engine/GameObject.h"
#include "engine/Component.h"

GameObject::GameObject() {
    isDead = false;
}

GameObject::~GameObject() {} 

void GameObject::Update(float dt) {
    for(auto& cpt : components) {
        cpt->Update(dt);
    }
}

void GameObject::Render() {
    for(auto& cpt : components) {
        cpt->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(shared_ptr<Component> cpt) {
    components.emplace_back(cpt);
}

void GameObject::RemoveComponent(shared_ptr<Component> cpt) {
    // ? What would happen if the components change during the loop (impossible right?)?
    for(auto it = components.begin(); it != components.end(); ) {
        if(*it == cpt) {
            it = components.erase(it);
            break;  // * Each component should have just 1 pointer.
        }
        else {
            it++;
        }
    }
}

shared_ptr<Component> GameObject::GetComponent(string type) {
    for(auto& cpt : components) {
        if(cpt->Is(type)) {
            return cpt;
        }
    }

    return shared_ptr<Component>{};
}