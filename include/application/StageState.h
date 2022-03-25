#ifndef __STAGESTATE_H__
#define __STAGESTATE_H__

#include "engine/Sprite.h"
#include "engine/Music.h"
#include "engine/Camera.h"
#include "engine/State.h"
#include <vector>
#include <memory>

class TileSet;

class StageState : public State {
    private:
        Music bgMusic;

        Sprite* bgSprite;
        TileSet* tileSet;

        std::vector<std::weak_ptr<Component>> aliens;
        
    public:
        StageState();
        ~StageState();

        void Start() override;
        void Pause() override {};
        void Resume() override {};

        void LoadAssets() override;
        
        // void UpdateArray(float dt) override;
        // void RenderArray() override;

        void Update(float dt = 0.0) override;
        void Render() override;
        void Input();

        void AddEnemy(int mouseX, int mouseY);
};

#endif
