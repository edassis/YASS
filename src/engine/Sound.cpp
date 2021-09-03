#include "engine/Sound.h"

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
    if(chunk == nullptr) return;

    Stop();
    Mix_FreeChunk(chunk);
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
    Mix_Chunk* nchunk = Mix_LoadWAV(file.c_str());
    if(nchunk == nullptr) {
        cout << "Failed to open sound file (" << file << "): " << Mix_GetError() << endl;
        return;
    }
    chunk = nchunk;
}

bool Sound::IsOpen() {
    return chunk != nullptr;
}

void Sound::Update(float dt) {}

void Sound::Render() {}

bool Sound::Is(string type) { return "Sound" == type; }