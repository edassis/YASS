#include "engine/Music.h"

#define INCLUDE_SDL_MIXER
#include "engine/SDL_include.h"
#include "engine/Resources.h"
#include <iostream>

using std::cout;
using std::endl;

Music::Music() {
    music = nullptr;
}

Music::Music(string file) {
    this->Open(file);
    this->Play();
}

Music::~Music() {}

void Music::Play(int times) {
    int _error = Mix_PlayMusic(this->music, times);
    if(_error) {
        cout << "Failed to play music:" << Mix_GetError() << endl;
    }
}

void Music::Stop(int msToStop) {
    int _success = Mix_FadeOutMusic(msToStop);
    if(!_success) {
        cout << "Failed to stop music:" << Mix_GetError() << endl;
    }
}

void Music::Open(string file) {
    this->music = Resources::GetInstance().GetMusic(file);
}

bool Music::IsOpen() {
    return (this->music != nullptr) ? true : false;
}