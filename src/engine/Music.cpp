#include "engine/Music.h"

#define INCLUDE_SDL_MIXER
#include "engine/SDL_include.h"
#include "engine/Resources.h"
#include <iostream>

Music::Music() {
    music = nullptr;
}

Music::Music(std::string file) {
    this->Open(file);
    this->Play();
}

Music::~Music() {}

void Music::Play(int times) {
    int _error = Mix_PlayMusic(this->music, times);
    if(_error) {
        std::cout << "Error! Music::Play() failed to play a music:" << Mix_GetError() << std::endl;
    }
}

void Music::Stop(int msToStop) {
    int _success = Mix_FadeOutMusic(msToStop);
    if(!_success) {
        std::cout << "Error! Music::Stop() failed to stop the music:" << Mix_GetError() << std::endl;
    }
}

void Music::Open(std::string file) {
    this->music = Resources::GetInstance().GetMusic(file);
}

bool Music::IsOpen() {
    return (this->music != nullptr) ? true : false;
}