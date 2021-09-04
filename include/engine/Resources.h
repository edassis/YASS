#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "engine/SDL_include.h"
#include "memory"
#include <unordered_map>
#include <string>

class Resources {
    private:
        std::unordered_map<std::string, SDL_Texture*> imageTable;
        std::unordered_map<std::string, Mix_Music*> musicTable;
        std::unordered_map<std::string, Mix_Chunk*> soundTable;

        Resources();

    public:
        ~Resources();
        Resources(const Resources&) = delete;
        Resources(const Resources&&) = delete;
        void operator=(const Resources&) = delete;

        static Resources& GetInstance();

        SDL_Texture* GetImage(std::string file);
        void ClearImages();
        Mix_Music* GetMusic(std::string file);
        void ClearMusics();
        Mix_Chunk* GetSound(std::string file);
        void ClearSounds();
};

#endif