#ifndef __STATE_H__
#define __STATE_H__

#include "engine/Sprite.h"
#include "engine/Music.h"
#include "engine/Camera.h"
#include <vector>
#include <memory>

class State {
    private:
        std::weak_ptr<Sprite> bg;
        Music music;
        std::shared_ptr<Camera> currentCamera;
        std::weak_ptr<GameObject> player;
        std::vector<std::shared_ptr<GameObject>> objectArray;
        
        bool quitRequested;
        bool started;
        
    public:
        State();
        ~State();

        void Start();

        bool QuitRequested();
        void LoadAssets();

        void Update(float dt = 0.0);
        void Render();
        void Input();

        std::weak_ptr<GameObject> AddObject(GameObject& go);
        std::weak_ptr<GameObject> GetObjectPtr(GameObject& go);

        void AddEnemy(int mouseX, int mouseY);
        Camera& GetCamera();
        std::weak_ptr<GameObject> GetPlayerPointer();
};

#endif