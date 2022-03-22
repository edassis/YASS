#include "application/TitleState.h"
#include "application/StageState.h"
#include "engine/Game.h"
#include "engine/Sprite.h"
#include "engine/GameObject.h"
#include "engine/InputManager.h"
#include "engine/CameraFollower.h"

TitleState::TitleState() {
    auto* titleGO = new GameObject();
    titleGO->AddComponent(*new CameraFollower(*titleGO));
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
    quitRequested = InputManager::GetInstance().QuitRequested();
    quitRequested |= InputManager::GetInstance().KeyPress(KEYS::ESCAPE_KEY);
    auto nextState = InputManager::GetInstance().KeyPress(KEYS::SPACE_KEY);

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