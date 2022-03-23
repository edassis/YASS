#ifndef __MUSIC_H__
#define __MUSIC_H__

#define INCLUDE_SDL_MIXER
#include "engine/SDL_include.h"
#include <iostream>
#include <memory>

class Music {
    private:
        std::shared_ptr<Mix_Music> music;
    public:
        Music();
        Music(std::string file);
        ~Music();

        void Play(int times = -1);
        void Stop(int msToStop = 300);
        void Open(std::string file);
        bool IsOpen();
};

#endif