#ifndef __MUSIC_H__
#define __MUSIC_H__

#define INCLUDE_SDL_MIXER
#include "engine/SDL_include.h"
#include <iostream>

using std::string;

class Music {
    public:
        Music();
        Music(string file);
        ~Music();
        void Play(int times = -1);
        void Stop(int msToStop = 1500);
        void Open(string file);
        bool IsOpen();
    private:
        Mix_Music *music;
};

#endif