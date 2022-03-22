#include "engine/State.h"
#include "engine/Camera.h"
#include "engine/Collider.h"

State::State() : currentCamera(new Camera()) {
    popRequested = false;
    quitRequested = false;
}

State::~State() {}

void State::Start() {
    LoadAssets();

    for(uint32_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }
    started = true;
}

void State::StartArray() {}

bool State::QuitRequested() {
    return quitRequested;
}

std::weak_ptr<GameObject> State::AddObject(GameObject& go) {
    if(started) {
        go.Start();
    }

    auto spGO = std::shared_ptr<GameObject>(&go);
    
    objectArray.push_back(spGO);

    return std::weak_ptr<GameObject>(spGO);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject& go) {
    for(auto& each : objectArray) {
        if(each.get() == &go) {
            return std::weak_ptr<GameObject>(each);
        }
    }

    return std::weak_ptr<GameObject>();
}

Camera& State::GetCamera() {
    return *currentCamera;
}

std::weak_ptr<GameObject> State::GetPlayerPointer() {
    return player;
}

void State::Update(float dt) {
    // Atualização dos estados das entidades, testes de colisões 
    struct ColliderInfo {
        std::shared_ptr<GameObject> spGO;
        std::shared_ptr<Collider> spCollider;
    };
    std::vector<ColliderInfo> activeColliders;

    // Update GameObjects 
    for(uint32_t i = 0; i < objectArray.size();) {
        objectArray[i]->Update(dt);

        if(objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin()+i);
            continue;
        } 

        auto spGO = objectArray[i];
        if(auto spCollider = std::dynamic_pointer_cast<Collider>(spGO->GetComponent("Collider").lock())) {
            activeColliders.push_back(ColliderInfo{spGO, spCollider});
        }

        i++;
    }
    
    // Check collisions
    for(uint32_t i = 0; i < activeColliders.size(); i++) {
        for(uint32_t j = i+1; j < activeColliders.size(); j++) {
            auto ColliderInfo1 = activeColliders[i];
            auto ColliderInfo2 = activeColliders[j];

            if(ColliderInfo1.spCollider->IsColliding(ColliderInfo2.spCollider->box, ColliderInfo2.spGO->angle)) {
                // Notify both
                ColliderInfo1.spGO->NotifyCollision(*ColliderInfo2.spGO);
                ColliderInfo2.spGO->NotifyCollision(*ColliderInfo1.spGO);
            }
        }
    }

    currentCamera->Update(dt);
}

void State::Render() {
    for(auto it = objectArray.begin(); it != objectArray.end(); it++) {
        (*it)->Render();
    }
}