#include "application/EndState.h"
#include "application/StageState.h"
#include "engine/Game.h"
#include "engine/GameObject.h"
#include "engine/Sprite.h"
#include "engine/Music.h"
#include "engine/InputManager.h"

#include "application/GameData.h"

EndState::EndState() {
    auto* GO = new GameObject();
    
    if(GameData::GetInstance().playerVictory) {
        GO->AddComponent(*new Sprite(*GO, "assets/img/win.jpg"));
        bgMusic.Open("assets/audio/endStateWin.ogg");
    } else {
        GO->AddComponent(*new Sprite(*GO, "assets/img/lose.jpg"));
        bgMusic.Open("assets/audio/endStateLose.ogg");
    }

    AddObject(*GO);
}

EndState::~EndState() {}

void EndState::Start() {
    bgMusic.Play();
    State::Start();
}

void EndState::LoadAssets() {}

void EndState::Pause() {}

void EndState::Resume() {}

void EndState::Update(float dt) {
    quitRequested = InputManager::GetInstance().QuitRequested();
    quitRequested |= InputManager::GetInstance().KeyPress(KEYS::ESCAPE_KEY);
    auto nextState = InputManager::GetInstance().KeyPress(KEYS::SPACE_KEY);

    if(nextState) {
        quitRequested = true;
        Game::GetInstance().Push(new StageState());
    }
    State::Update(dt);
}

void EndState::Render() {
    State::Render();
}