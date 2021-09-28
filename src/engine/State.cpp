#include "engine/State.h"

#define INCLUDE_SDL
#include "engine/SDL_include.h"
#include "engine/Mat.h"
#include "engine/Game.h"
#include "engine/GameObject.h"
#include "engine/Face.h"
#include "engine/Sound.h"
#include "engine/TileMap.h"
#include "engine/TileSet.h"
#include "engine/InputManager.h"
#include "engine/CameraFollower.h"
#include <iostream>

State::State() : music(), currentCamera(new Camera()) {
    quitRequested = false;
    started = false;

    GameObject* goBG = new GameObject();

    goBG->AddComponent(std::make_shared<CameraFollower>(*goBG));    // * CameraFollower must update "go" position before Sprite's Render().
    
    std::shared_ptr<Sprite> spriteBG(new Sprite(*goBG));
    goBG->AddComponent(spriteBG);
	this->bg = spriteBG;

	objectArray.emplace_back(goBG);

    GameObject* goTileMap = new GameObject();
	TileSet* ts = new TileSet(64, 64, "assets/img/tileset.png");
	goTileMap->AddComponent(std::make_shared<TileMap>(*goTileMap, "assets/map/tileMap.txt", ts));
 
    objectArray.emplace_back(goTileMap);
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
        
        AddEnemy(mouseX, mouseY);
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
    
    currentCamera->Update(dt);
    // std::cout << "GOs " << objectArray.size() << std::endl;
}

void State::Render() {
    // Renderização do estado do jogo (entidades, cenários, HUD, etc.).
    if(bg) {
        bg->Render();
    }

    for(auto it = objectArray.begin(); it != objectArray.end(); it++) {
        (*it)->Render();
    }
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    if(go == nullptr) {
        std::cout << "Warning! State::AddObject() has nullptr as parameter" << std::endl;
        return std::weak_ptr<GameObject>();
    }

    if(started) {
        go->Start();
    }

    auto ptGO = std::shared_ptr<GameObject>(go);
    
    objectArray.push_back(ptGO);

    return std::weak_ptr<GameObject>(ptGO);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for(auto& each : objectArray) {
        if(each.get() == go) {
            return std::weak_ptr<GameObject>(each);
        }
    }

    return std::weak_ptr<GameObject>();
}

void State::AddEnemy(int mouseX, int mouseY) {
    // First enemy
	GameObject* go = new GameObject();
    Sprite* spt = new Sprite(*go, "assets/img/penguinface.png");
	Sound* sound = new Sound(*go, "assets/audio/boom.wav");
	Face* face = new Face(*go);

    // * Consider camera movimentation
    const auto& cameraPos = Game::GetState().GetCamera().pos;

    mat::Vec2 pos((float)mouseX, (float)mouseY); 
    pos += cameraPos;

	// * Centralize image on the cursor
    pos.x -= float(spt->GetWidth()/2);
    pos.y -= float(spt->GetHeight()/2);

	go->box.x = pos.x;
    go->box.y = pos.y;

	go->AddComponent(std::shared_ptr<Component>(spt));
	go->AddComponent(std::shared_ptr<Component>(face));
	go->AddComponent(std::shared_ptr<Component>(sound));

    auto ptGO = AddObject(go);
    
    GetCamera().Follow(ptGO);
}

Camera& State::GetCamera() {
    return *currentCamera;
}