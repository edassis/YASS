#ifndef __STATE_H__
#define __STATE_H__

#include "engine/Sprite.h"
#include "engine/Music.h"

class State {
    private:
        Sprite bg;
        Music music;
        bool quitRequested;
    public:
        State();

        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
};

#endif