#include "engine/State.h"

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

#include "application/Alien.h"

#include <iostream>

State::State() : music(), currentCamera(new Camera()) {
    quitRequested = false;
    started = false;

    GameObject* BGGameObj = new GameObject();
    CameraFollower* BGGameFol = new CameraFollower(*BGGameObj);
    BGGameObj->AddComponent(*BGGameFol);
    Sprite* BGSprite = new Sprite(*BGGameObj);
    auto pBGSprite = BGGameObj->AddComponent(*BGSprite).lock();
    this->bg = std::dynamic_pointer_cast<Sprite>(pBGSprite);
    AddObject(*BGGameObj);

    GameObject* TMGameObj = new GameObject();
	TileSet* TMTileSet = new TileSet(64, 64, "assets/img/tileset.png");
    TileMap* TM = new TileMap(*TMGameObj, "assets/map/tileMap.txt", TMTileSet);
    TMGameObj->AddComponent(*TM);
    AddObject(*TMGameObj);

    auto* alienGO = new GameObject();
    auto* alien = new Alien(*alienGO, 3);
    alienGO->box.Centralize(mat::Vec2(300.0f, 200.0f));
    alienGO->AddComponent(*alien);
    AddObject(*alienGO);
}

State::~State() {}

void State::Start() {
    LoadAssets();

    for(uint32_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }
    started = true;
}

bool State::QuitRequested() {
    return this->quitRequested;
}

void State::LoadAssets() {
    // Pré-carrega os assets.
    if(auto pBG = bg.lock()) {
        pBG->Open("assets/img/ocean.jpg");
    }

    this->music.Open("assets/audio/stageState.ogg");
    if(this->music.IsOpen()) {
        this->music.Play();
    }
}

void State::Update(float dt) {
    // Atualização dos estados das entidades, testes de colisões e checagem relativa de encerramento do jogo.
    quitRequested = InputManager::GetInstance().QuitRequested();
    quitRequested |= InputManager::GetInstance().KeyPress(KEYS::ESCAPE_KEY);

    for(uint32_t i = 0; i < objectArray.size(); ) {
        objectArray[i]->Update(dt);

        if(objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin()+i);
        }
        else {
            i++;
        }
    }
    
    currentCamera->Update(dt);
    // std::cout << "GOs " << objectArray.size() << std::endl;
}

void State::Render() {
    // Renderização do estado do jogo (entidades, cenários, HUD, etc.).
    auto ptBG = bg.lock();
    if(ptBG) {
        ptBG->Render();
    }

    for(auto it = objectArray.begin(); it != objectArray.end(); it++) {
        (*it)->Render();
    }
}

std::weak_ptr<GameObject> State::AddObject(GameObject& go) {
    if(started) {
        go.Start();
    }

    auto ptGO = std::shared_ptr<GameObject>(&go);
    
    objectArray.push_back(ptGO);

    return std::weak_ptr<GameObject>(ptGO);
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