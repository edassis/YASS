#include "application/TitleState.h"
#include "application/StageState.h"
#include "engine/Game.h"
#include "engine/Sprite.h"
#include "engine/GameObject.h"
#include "engine/InputManager.h"

TitleState::TitleState() {
    auto* titleGO = new GameObject();
    titleGO->AddComponent(*new Sprite(*titleGO, "assets/img/title.jpg"));
    AddObject(*titleGO);
}

void TitleState::Start() {
    State::Start();
}

void TitleState::LoadAssets() {}

void TitleState::Pause() {}

void TitleState::Resume() {}

TitleState::~TitleState() {}

void TitleState::Update(float dt) {
    auto nextState = InputManager::GetInstance().QuitRequested();
    nextState |= InputManager::GetInstance().KeyPress(KEYS::ESCAPE_KEY);

    if(nextState) {
        Game::GetInstance().Push(new StageState());
    }
    State::Update(dt);
}

void TitleState::Render() {
    State::Render();
}

// void TitleState::UpdateArray(float dt) {}

// void TitleState::RenderArray() {}