#ifndef __STATE_H__
#define __STATE_H__

#include "engine/Sprite.h"
#include "engine/Music.h"
#include "engine/Camera.h"
#include <vector>
#include <memory>

class State {
    private:
        std::shared_ptr<Sprite> bg;
        Music music;
        std::shared_ptr<Camera> currentCamera;
        std::vector<std::unique_ptr<GameObject>> objectArray;
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
        
        Camera& GetCamera();
};

#endif