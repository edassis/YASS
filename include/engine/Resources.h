#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "engine/SDL_include.h"
#include <memory>
#include <unordered_map>
#include <string>

class Resources {
    private:
        std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
        std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
        std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;
        std::unordered_map<std::string, std::shared_ptr<TTF_Font>> fontTable;

        Resources();

    public:
        ~Resources();
        Resources(const Resources&) = delete;
        Resources(const Resources&&) = delete;
        void operator=(const Resources&) = delete;

        static Resources& GetInstance();

        std::shared_ptr<SDL_Texture> GetImage(std::string file);
        void ClearImages();
        std::shared_ptr<Mix_Music> GetMusic(std::string file);
        void ClearMusics();
        std::shared_ptr<Mix_Chunk> GetSound(std::string file);
        void ClearSounds();
        std::shared_ptr<TTF_Font> GetFont(std::string file, int fontSize);
        void ClearFonts();
};

#endif