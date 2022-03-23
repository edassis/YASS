#ifndef __SOUND_H__
#define __SOUND_H__

#define INCLUDE_SDL_MIXER
#include "engine/SDL_include.h"
#include "engine/Component.h"
#include <iostream>
#include <memory>

class Sound : public Component {
    private:
        std::shared_ptr<Mix_Chunk> chunk;
        int channel;
    public:
        Sound(GameObject& associated);
        Sound(GameObject& associated, std::string file);
        ~Sound();

        void Play(int times = 1);
        void Stop();
        void Open(std::string file);
        bool IsOpen();
        bool IsPlaying();

        /* Component */
        void Update(float dt) override;
        void Render() override;
        bool Is(std::string type) override;
};

#endif