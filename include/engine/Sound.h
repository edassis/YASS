#ifndef __SOUND_H__
#define __SOUND_H__

// #define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "engine/SDL_include.h"
#include "engine/Component.h"
#include <iostream>

using std::string;

class Sound : public Component {
    private:
        Mix_Chunk *chunk;
        int channel;
    public:
        Sound(GameObject &associated);
        Sound(GameObject &associated, string file);
        ~Sound();

        void Play(int times = 1);
        void Stop();
        void Open(string file);
        bool IsOpen();

        /* Component */
        void Update(float dt);
        void Render();
        bool Is(string type);
};

#endif