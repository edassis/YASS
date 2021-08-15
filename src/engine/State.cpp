#include "engine/State.h"

#define INCLUDE_SDL
#include "engine/SDL_include.h"
#include <stdio.h>

using std::cout;
using std::endl;

State::State() {
    this->quitRequested = false;

    this->bg = Sprite();
    this->music = Music();
}

State::~State() {}

bool State::QuitRequested() {
    return this->quitRequested;
}

void State::LoadAssets() {
    // Pré-carrega os assets.
    this->bg.Open("assets/img/ocean.jpg");
    this->music.Open("assets/audio/boom.wav");
    if(this->music.IsOpen()) {
        this->music.Play();
    }
}

void State::Update(float dt) {
    // Atualização dos estados das entidades, testes de colisões e checagem relativa de encerramento do jogo.
    bool is_quit = SDL_QuitRequested();
    if(is_quit) quitRequested = true;
}

void State::Render() {
    // Renderização do estado do jogo (entidades, cenários, HUD, etc.).
    this->bg.Render(0, 0);
}