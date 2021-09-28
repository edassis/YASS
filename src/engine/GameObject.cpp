#include "engine/GameObject.h"
#include "engine/Component.h"

GameObject::GameObject() {
    isDead = false;
    started = false;
}

GameObject::~GameObject() {} 

void GameObject::Start() {
    for(uint32_t i = 0; i < components.size(); i++) {
        components[i]->Start();
    }
    started = true;
}

void GameObject::Update(float dt) {
    for(uint32_t i = 0; i < components.size(); i++) {
        auto component = components[i];
        component->Update(dt);
    }
}

void GameObject::Render() {
    for(uint32_t i = 0; i < components.size(); i++) {
        auto component = components[i];
        component->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(std::shared_ptr<Component> cpt) {
    if(cpt == nullptr) {
        std::cout << "Warning! GameObject::AddComponent() has nullptr as parameter" << std::endl;
        return;
    }

    if(started) {
        cpt->Start();
    }

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