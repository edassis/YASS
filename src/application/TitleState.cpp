#include "application/TitleState.h"
#include "application/StageState.h"
#include "engine/Game.h"
#include "engine/Sprite.h"
#include "engine/GameObject.h"
#include "engine/InputManager.h"
#include "engine/CameraFollower.h"
#include "engine/Text.h"

TitleState::TitleState() {
    auto* titleGO = new GameObject();
    titleGO->AddComponent(*new CameraFollower(*titleGO));
    titleGO->AddComponent(*new Sprite(*titleGO, "assets/img/title.jpg"));
    AddObject(*titleGO);

    auto* textGO = new GameObject();
    std::string textString = "Aperte \"Espaco\" para continuar";
    SDL_Color textColor = {0, 0, 0, 0xff};
    auto* textComponent = new Text(*textGO, "assets/font/Call me maybe.ttf", 14, Text::BLENDED, textString, textColor);
    textGO->AddComponent(*textComponent);
    AddObject(*textGO);
    
    textGO->box.Centralize(mat::Vec2{480.f, 500.f});
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