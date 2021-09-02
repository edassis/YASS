#include "engine/State.h"

#define INCLUDE_SDL
#include "engine/SDL_include.h"
#include "engine/Mat.h"
#include "engine/GameObject.h"
#include "engine/Face.h"
#include "engine/Sound.h"
#include <iostream>

using std::cout;
using std::endl;

using namespace mat;

State::State() : music() {
    this->quitRequested = false;

    GameObject* go = new GameObject();
    this->bg = unique_ptr<Sprite>(new Sprite(*go));
}

State::~State() {} // ? Preciso explicitamente esvaziar objectArray?

bool State::QuitRequested() {
    return this->quitRequested;
}

void State::LoadAssets() {
    // Pré-carrega os assets.
    this->bg->Open("assets/img/ocean.jpg");

    // this->music.Open("assets/audio/boom.wav");
    // if(this->music.IsOpen()) {
    //     this->music.Play();
    // }
}

void State::Update(float dt) {
    // Atualização dos estados das entidades, testes de colisões e checagem relativa de encerramento do jogo.
    Input();
    for(unsigned i = 0; i < objectArray.size(); ) {
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

void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {
		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {
			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				// GameObject* go = (GameObject*) objectArray[i].get();
				GameObject* go = static_cast<GameObject*>(objectArray[i].get());
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.Contains( {(float)mouseX, (float)mouseY} )) {
					Face* face = (Face*) go->GetComponent("Face").get();
					if (face != nullptr) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2(200, 0).Rotated(-PI + PI*(rand() % 1001)/500.0) + Vec2(mouseX, mouseY);
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

void State::AddObject(int mouseX, int mouseY) {
    // Primeiro inimigo
	GameObject *go = new GameObject();
    Sprite* spt = new Sprite(*go, "assets/img/penguinface.png");
	Face* fc = new Face(*go);
	Sound* s = new Sound(*go, "assets/audio/boom.wav");

	// * Centralize image on the cursor
	go->box.x = mouseX - spt->GetWidth()/2;
    go->box.y = mouseY - spt->GetHeight()/2;

	go->AddComponent(std::shared_ptr<Component>(spt));
	go->AddComponent(std::shared_ptr<Component>(fc));
	go->AddComponent(std::shared_ptr<Component>(s));
    objectArray.emplace_back(go);
}