#include "engine/StageState.h"

#define INCLUDE_SDL
#include "engine/SDL_include.h"
#include "engine/Mat.h"
#include "engine/Game.h"
#include "engine/GameObject.h"
#include "engine/Sound.h"
#include "engine/TileMap.h"
#include "engine/TileSet.h"
#include "engine/InputManager.h"
#include "engine/CameraFollower.h"
#include "engine/Collider.h"

#include "application/Alien.h"
#include "application/PenguinBody.h"

#include <iostream>

StageState::StageState() : bgMusic() {
    quitRequested = false;
    started = false;

    GameObject* BGGameObj = new GameObject();
    CameraFollower* BGGameFol = new CameraFollower(*BGGameObj);
    BGGameObj->AddComponent(*BGGameFol);
    bgSprite = new Sprite(*BGGameObj);
    BGGameObj->AddComponent(*bgSprite);
    AddObject(*BGGameObj);

    GameObject* TMGameObj = new GameObject();
	tileSet = new TileSet(64, 64, "assets/img/tileset.png");
    TileMap* TM = new TileMap(*TMGameObj, "assets/map/tileMap.txt", tileSet);
    TMGameObj->AddComponent(*TM);
    AddObject(*TMGameObj);

    auto* alienGO = new GameObject();
    auto* alien = new Alien(*alienGO, 3);
    alienGO->box.Centralize(mat::Vec2(300.0f, 200.0f));
    alienGO->AddComponent(*alien);
    AddObject(*alienGO);

    auto* penguinGO = new GameObject();
    auto* penguin = new PenguinBody(*penguinGO);
    penguinGO->box.Centralize(mat::Vec2(500.0f, 280.0f));
    penguinGO->AddComponent(*penguin);
    auto wpPenguin = AddObject(*penguinGO);
    player = wpPenguin;
    GetCamera().Follow(wpPenguin);
}

StageState::~StageState() {}

void StageState::Start() {
    LoadAssets();

    for(uint32_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }
    started = true;
}

// bool StageState::QuitRequested() {
//     return this->quitRequested;
// }

void StageState::LoadAssets() {
    // Pré-carrega os assets.
    if(bgSprite) {
        bgSprite->Open("assets/img/ocean.jpg");
    }

    bgMusic.Open("assets/audio/stageState.ogg");
    if(bgMusic.IsOpen()) {
        bgMusic.Play();
    }
}

void StageState::Update(float dt) {
    // Atualização dos estados das entidades, testes de colisões e checagem relativa de encerramento do jogo.
    quitRequested = InputManager::GetInstance().QuitRequested();
    quitRequested |= InputManager::GetInstance().KeyPress(KEYS::ESCAPE_KEY);

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

void StageState::Render() {
    // Renderização do estado do jogo (entidades, cenários, HUD, etc.).
    // if(bgSprite) {
    //     bgSprite->Render();
    // }

    for(auto it = objectArray.begin(); it != objectArray.end(); it++) {
        (*it)->Render();
    }
}

void StageState::UpdateArray(float dt) {}

void StageState::RenderArray() {}
