#include "engine/Resources.h"
#include "engine/Game.h"
#include <iostream>

Resources::Resources() {}

Resources::~Resources() {}

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
    auto it = imageTable.find(file);
    if(it != imageTable.end()) return it->second; 

    auto spImage = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str()),
            [](SDL_Texture* texture) {
                SDL_DestroyTexture(texture);
            }
    );
    if(!spImage) {
        std::cout << "Error! Resources::GetImage() failed to load image: " << IMG_GetError() << std::endl;
        return {};
    }

    imageTable.emplace(file, spImage);
    return spImage;
}

void Resources::ClearImages() {
    for(auto it = imageTable.begin(); it != imageTable.end();) {
        if(it->second.unique()) {
            it = imageTable.erase(it);
        } else {
            it++;
        }
    }
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file) {
    auto it = musicTable.find(file);
    if(it != musicTable.end()) return it->second;

    auto spMusic = std::shared_ptr<Mix_Music>(Mix_LoadMUS(file.c_str()), 
            [](Mix_Music* music) {
                Mix_FreeMusic(music);
            }
    );
    if(!spMusic) {
        std::cout << "Error! Resources::GetMusic() failed to load music: " << Mix_GetError() << std::endl;
        return {};
    }
    
    musicTable.emplace(file, spMusic);
    return spMusic;
}

void Resources::ClearMusics() {
    for(auto it = musicTable.begin(); it != musicTable.end();) {
        if(it->second.unique()) {
            it = musicTable.erase(it);
        } else {
            it++;
        }
    }
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file) {
    auto it = soundTable.find(file);
    if(it != soundTable.end()) return it->second;

    auto spSound = std::shared_ptr<Mix_Chunk>(Mix_LoadWAV(file.c_str()),
            [](Mix_Chunk* sound) {
                Mix_FreeChunk(sound); 
            }
    );
    if(!spSound) {
        std::cout << "Error! Resources::GetSound() failed to load sound: " << Mix_GetError() << std::endl;
        return {};
    }
    
    soundTable.emplace(file, spSound);
    return spSound;
}

void Resources::ClearSounds() {
    for(auto it = soundTable.begin(); it != soundTable.end();) {
        if(it->second.unique()) {
            it = soundTable.erase(it);
        } else {
            it++;
        }
    }
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int fontSize) {
    auto it = fontTable.find(file+std::to_string(fontSize));
    if(it != fontTable.end()) return it->second;

    auto spFont = std::shared_ptr<TTF_Font>(TTF_OpenFont(file.c_str(), fontSize),
            [](TTF_Font* font) {
                TTF_CloseFont(font); 
            }
    );
    if(!spFont) {
        std::cout << "Error! Resources::GetFont() failed to load font: " << TTF_GetError() << std::endl;
        return {};
    }
    
    fontTable.emplace(file+std::to_string(fontSize), spFont);
    return spFont;
}

void Resources::ClearFonts() {
    for(auto it = fontTable.begin(); it != fontTable.end();) {
        if(it->second.unique()) {
            it = fontTable.erase(it);
        } else {
            it++;
        }
    }
}

Resources& Resources::GetInstance() {
    static Resources rsc;
    return rsc; 
}