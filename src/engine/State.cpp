#include "engine/State.h"
#include "engine/Camera.h"

State::State() : currentCamera(new Camera()) {}

State::~State() {}

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
