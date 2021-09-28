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

std::weak_ptr<Component> GameObject::AddComponent(Component& cpt) {
    // if(cpt == nullptr) {
    //     std::cout << "Warning! GameObject::AddComponent() has nullptr as parameter" << std::endl;
    //     return;
    // }

    if(started) {
        cpt.Start();
    }

    auto ptCpt = std::shared_ptr<Component>(&cpt);
    components.push_back(ptCpt);
    return std::weak_ptr<Component>(ptCpt);
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

std::weak_ptr<Component> GameObject::GetComponent(std::string type) {
    for(auto& cpt : components) {
        if(cpt->Is(type)) {
            return cpt;
        }
    }

    return std::weak_ptr<Component>{};
}