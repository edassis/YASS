#ifndef __STATE_H__
#define __STATE_H__

#include <vector>
#include <memory>
#include "engine/GameObject.h"

class Camera;

class State {
    protected:
        bool popRequested;
        bool quitRequested;
        bool started;
        
        std::vector<std::shared_ptr<GameObject>> objectArray;        
        
        void StartArray();
        virtual void UpdateArray(float dt) =0;
        virtual void RenderArray() =0;
        
        std::shared_ptr<Camera> currentCamera;
        std::weak_ptr<GameObject> player;

    public:
        State();
        virtual ~State();

        virtual void LoadAssets() =0;
        virtual void Update(float dt) =0;
        virtual void Render() =0;

        virtual void Start() =0;
        virtual void Pause() =0;
        virtual void Resume() =0;

        virtual std::weak_ptr<GameObject> AddObject(GameObject& go);
        virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject& go);

        bool PoolRequested();
        bool QuitRequested();

        Camera& GetCamera();
        std::weak_ptr<GameObject> GetPlayerPointer();

};

#endif
