#ifndef __TITLESTATE_H__
#define __TITLESTATE_H__

#include "engine/State.h"

class TitleState : public State {
    public:
        TitleState();
        ~TitleState();

        void LoadAssets() override;
        void Update(float dt) override;
        void Render() override;

        void Start() override;
        void Pause() override;
        void Resume() override;
};

#endif