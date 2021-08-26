#ifndef __STATE_H__
#define __STATE_H__

#include "engine/Sprite.h"
#include "engine/Music.h"
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

class State {
    private:
        unique_ptr<Sprite> bg;
        Music music;
        vector<unique_ptr<GameObject>> objectArray;
        bool quitRequested;
    public:
        State();
        ~State();

        bool QuitRequested();
        void LoadAssets();
        void Update(float dt = 0.0);
        void Render();
        void Input();
        void AddObject(int mouseX, int mouseY);
};

#endif