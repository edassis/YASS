#include "engine/GameObject.h"
#include "engine/Component.h"

GameObject::GameObject() {
    isDead = false;
}

GameObject::~GameObject() {} 

void GameObject::Update(float dt) {
    for(auto &cpt : components) {
        cpt->Update(dt);
    }
}

void GameObject::Render() {
    for(auto &cpt : components) {
        cpt->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(unique_ptr<Component> cpt) {
    components.push_back(std::move(cpt));
}

void GameObject::RemoveComponent(unique_ptr<Component> cpt) {
    // Q: what would happen if components change during the loop (impossible right?)?
    for(auto it = components.begin(); it != components.end(); ) {
        if(*it == cpt) {
            // delete *it;
            it = components.erase(it);
            break;  // each component should have just 1 pointer.
        }
        else {
            it++;
        }
    }
}

unique_ptr<Component> GameObject::GetComponent(string type) {
    for(auto &cpt : components) {
        if(cpt->Is(type)) {
            return std::move(cpt);
        }
    }

    return unique_ptr<Component>{};
}