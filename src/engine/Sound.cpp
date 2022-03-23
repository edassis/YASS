#include "engine/Sound.h"
#include "engine/Resources.h"

Sound::Sound(GameObject& associated) : Component(associated) {
    chunk = nullptr;
    channel = -1;
}

Sound::Sound(GameObject& associated, std::string file) : Component(associated) {
    chunk = nullptr;
    Open(file);
}

Sound::~Sound() {
    Stop();
}

void Sound::Play(int times) {
    channel = Mix_PlayChannel(-1, chunk.get(), times-1);
    if(channel == -1) {
        std::cout << "Error! Sound::Play() failed to play a sound: " << Mix_GetError() << std::endl;
    }
}

void Sound::Stop() {
    if(chunk == nullptr) return;

    Mix_HaltChannel(channel);
}

void Sound::Open(std::string file) {
    chunk = Resources::GetInstance().GetSound(file);
}

bool Sound::IsOpen() {
    return chunk != nullptr;
}

bool Sound::IsPlaying() {
    if (channel < 0) return false;
    
    return bool(Mix_Playing(channel));
}

void Sound::Update(float dt) {}

void Sound::Render() {}

bool Sound::Is(std::string type) { return "Sound" == type; }