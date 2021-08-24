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

Component* GameObject::GetComponent(string type) {
    for(auto each : components) {
        if(each->Is(type)) {
            return each;
        }
    }

    return nullptr;
}