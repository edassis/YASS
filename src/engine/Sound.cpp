#include "engine/Sound.h"
#include "engine/Resources.h"

using std::cout;
using std::endl;

Sound::Sound(GameObject& associated) : Component(associated) {
    chunk = nullptr;
    channel = -1;
}

Sound::Sound(GameObject& associated, string file) : Component(associated) {
    chunk = nullptr;
    Open(file);
}

Sound::~Sound() {
    Stop();
}

void Sound::Play(int times) {
    channel = Mix_PlayChannel(-1, chunk, times-1);
    if(channel == -1) {
        cout << "Error trying to play a sound: " << Mix_GetError() << endl;
    }
}

void Sound::Stop() {
    if(chunk == nullptr) return;

    Mix_HaltChannel(channel);
}

void Sound::Open(string file) {
    chunk = Resources::GetInstance().GetSound(file);
}

bool Sound::IsOpen() {
    return chunk != nullptr;
}

void Sound::Update(float dt) {}

void Sound::Render() {}

bool Sound::Is(string type) { return "Sound" == type; }