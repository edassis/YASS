#include "engine/GameObject.h"
#include "engine/Component.h"

GameObject::GameObject() {
    isDead = false;
}

GameObject::~GameObject() {} 

void GameObject::Update(float dt) {
    for(auto it = components.begin(); it != components.end(); it++) {
        auto cpt = *it;
        cpt->Update(dt);
    }
}

void GameObject::Render() {
    for(auto it = components.begin(); it != components.end(); it++) {
        auto cpt = *it;
        cpt->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(std::shared_ptr<Component> cpt) {
    components.push_back(std::move(cpt));
}

void GameObject::RemoveComponent(Component& cpt) {
    // ? What would happen if the components change during the loop (impossible right?)?
    for(auto it = components.begin(); it != components.end(); ) {
        if(it->get() == &cpt) {
            it = components.erase(it);
            break;  // * Each component should have just 1 pointer.
        }
        else {
            it++;
        }
    }
}

std::shared_ptr<Component> GameObject::GetComponent(std::string type) {
    for(auto& cpt : components) {
        if(cpt->Is(type)) {
            return cpt;
        }
    }

    return std::shared_ptr<Component>{};
}