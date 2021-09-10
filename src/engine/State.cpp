#include "engine/State.h"

#define INCLUDE_SDL
#include "engine/SDL_include.h"
#include "engine/Mat.h"
#include "engine/GameObject.h"
#include "engine/Face.h"
#include "engine/Sound.h"
#include "engine/TileMap.h"
#include "engine/TileSet.h"
#include "engine/InputManager.h"
#include <iostream>

State::State() : music() {
    this->quitRequested = false;

    GameObject* go = new GameObject();

	TileSet* ts = new TileSet(64, 64, "assets/img/tileset.png");

	go->AddComponent(std::make_shared<TileMap>(*go, "assets/map/tileMap.txt", ts));

	objectArray.emplace_back(go);
	
	this->bg = std::unique_ptr<Sprite>(new Sprite(*go));
}

State::~State() {} 

bool State::QuitRequested() {
    return this->quitRequested;
}

void State::LoadAssets() {
    // Pré-carrega os assets.
    this->bg->Open("assets/img/ocean.jpg");

    this->music.Open("assets/audio/stageState.ogg");
    if(this->music.IsOpen()) {
        this->music.Play();
    }
}

void State::Update(float dt) {
    // Atualização dos estados das entidades, testes de colisões e checagem relativa de encerramento do jogo.
    quitRequested = InputManager::GetInstance().QuitRequested();
    quitRequested |= InputManager::GetInstance().KeyPress(KEYS::ESCAPE_KEY);
    
    if (InputManager::GetInstance().KeyPress(KEYS::SPACE_KEY)) {
        int mouseX = InputManager::GetInstance().GetMouseX();
        int mouseY = InputManager::GetInstance().GetMouseY();
        
        AddObject(mouseX, mouseY);
    }

    for(uint32_t i = 0; i < objectArray.size(); ) {
        objectArray[i]->Update(dt);

        if(objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin()+i);
        }
        else {
            i++;
        }
    }
}


void State::Render() {
    // Renderização do estado do jogo (entidades, cenários, HUD, etc.).
    this->bg->Render();
    for(auto it = objectArray.begin(); it != objectArray.end(); it++) {
        (*it)->Render();
    }
}

void State::AddObject(int mouseX, int mouseY) {
    // Primeiro inimigo
	GameObject* go = new GameObject();
    Sprite* spt = new Sprite(*go, "assets/img/penguinface.png");
	Sound* s = new Sound(*go, "assets/audio/boom.wav");
	Face* fc = new Face(*go);

	// * Centralize image on the cursor
	go->box.x = float(mouseX - spt->GetWidth()/2);
    go->box.y = float(mouseY - spt->GetHeight()/2);

	go->AddComponent(std::shared_ptr<Component>(spt));
	go->AddComponent(std::shared_ptr<Component>(fc));
	go->AddComponent(std::shared_ptr<Component>(s));
    objectArray.emplace_back(go);
}