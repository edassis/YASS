#ifndef __ENDSTATE_H__
#define __ENDSTATE_H__

#include "engine/State.h"
#include "engine/Music.h"

class EndState : public State {
    Music bgMusic;

    public:
        EndState();
        ~EndState();

        void LoadAssets() override;
        void Update(float dt) override;
        void Render() override;

        void Start() override;
        void Pause() override;
        void Resume() override;
};

#endif