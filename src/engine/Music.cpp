#include "engine/Music.h"

#define INCLUDE_SDL_MIXER
#include "engine/SDL_include.h"
#include <iostream>

using std::cout;
using std::endl;

Music::Music() {
    this->music = nullptr;
}

Music::Music(string file) {
    this->Open(file);
    this->Play();
}

Music::~Music() {
    if(this->music == nullptr) return;  // Por que o desconstruct está sendo chamado?

    this->Stop();   
    Mix_FreeMusic(this->music);     // BUG? deve intenrromper o fadeout instantaneamente
}

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
    Mix_Music* newMusic = Mix_LoadMUS(file.c_str());
    if(newMusic == nullptr) {
        cout << "Failed to load file \"" << file << "\" :" << Mix_GetError() << endl;
    }
    this->music = newMusic;
}

bool Music::IsOpen() {
    return (this->music != nullptr) ? true : false;
}