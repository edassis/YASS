#include "engine/Resources.h"
#include "engine/Game.h"
#include <iostream>

Resources::Resources() {}

Resources::~Resources() {
    ClearImages();
    ClearMusics();
    ClearSounds();
}

SDL_Texture* Resources::GetImage(std::string file) {
    auto it = imageTable.find(file);
    if(it != imageTable.end()) return it->second; 

    SDL_Texture* image = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if(image == nullptr) {
        std::cout << "Error! Resources::GetImage() failed to load image: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    imageTable.emplace(file, image);
    return image;
}

void Resources::ClearImages() {
    for(auto& pair : imageTable) {
        SDL_DestroyTexture(pair.second);
    }
    imageTable.clear();
}

Mix_Music* Resources::GetMusic(std::string file) {
    auto it = musicTable.find(file);
    if(it != musicTable.end()) return it->second;

    Mix_Music* music = Mix_LoadMUS(file.c_str());
    if(music == nullptr) {
        std::cout << "Error! Resources::GetMusic() failed to load music: " << Mix_GetError() << std::endl;
        return nullptr;
    }
    
    musicTable.emplace(file, music);
    return music;
}

void Resources::ClearMusics() {
    for(auto& pair : musicTable) {
        Mix_FreeMusic(pair.second);
    }
    musicTable.clear();
}

Mix_Chunk* Resources::GetSound(std::string file) {
    auto it = soundTable.find(file);
    if(it != soundTable.end()) return it->second;

    Mix_Chunk* sound = Mix_LoadWAV(file.c_str());
    if(sound == nullptr) {
        std::cout << "Error! Resources::GetSound() failed to load sound: " << Mix_GetError() << std::endl;
        return nullptr;
    }
    
    soundTable.emplace(file, sound);
    return sound;
}

void Resources::ClearSounds() {
    for(auto& pair : soundTable) {
        Mix_FreeChunk(pair.second);
    }
    soundTable.clear();
}

Resources& Resources::GetInstance() {
    static Resources rsc;
    return rsc; 
}