#include "engine/GameObject.h"
#include "engine/Component.h"

GameObject::GameObject() {
    isDead = false;
}

GameObject::~GameObject() {
    for(auto p : components) {
        delete p; // we can change for unique_ptr
    }
    components.clear();
}

void GameObject::Update(float dt) {
    for(auto each : components) {
        each->Update(dt);
    }
}

void GameObject::Render() {
    for(auto each : components) {
        each->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component *cpt) {
    components.push_back(cpt);
}

void GameObject::RemoveComponent(Component *cpt) {
    for(unsigned i = 0; i < components.size(); i++) {
        if(components[i] == cpt) {
            delete components[i];
            components.erase(components.begin()+i);
            break;  // each component should have just 1 pointer.
        }
    }
}

Component* GameObject::GetComponent(string type) {
    for(auto each : components) {
        if(each->Is(type)) {
            return each;
        }
    }
}