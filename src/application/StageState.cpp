#include "application/StageState.h"

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
    State::Start(); 
}

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
    quitRequested = InputManager::GetInstance().QuitRequested();
    quitRequested |= InputManager::GetInstance().KeyPress(KEYS::ESCAPE_KEY);

    State::Update(dt);
}

void StageState::Render() {
    // Renderização do estado do jogo (entidades, cenários, HUD, etc.).
    // if(bgSprite) {
    //     bgSprite->Render();
    // }

    State::Render();
}

// void StageState::UpdateArray(float dt) {}

// void StageState::RenderArray() {}
