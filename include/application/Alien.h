#ifndef __ALIEN_H__
#define __ALIEN_H__

#include "engine/Component.h"
#include "engine/Mat.h"
#include "engine/Timer.h"
#include <string>
#include <vector>
#include <queue>
#include <memory>

class Alien : public Component {
    private:
        enum AlienState { MOVING, RESTING };
        AlienState state;
        float currentTime;
        Timer restTimer;
        mat::Vec2 destination; 

        int hp;
        mat::Vec2 speed;
        int nMinion;
        std::vector<std::weak_ptr<GameObject>> minionArray;

        void Shoot(float dt);
        void Move(float dt);

    public:
        Alien(GameObject& associated, int nMinion);
        ~Alien();

        static int alienCount;

        /* Component */
        void Start() override;
        void Update(float dt) override;
        void Render() override;
        bool Is(std::string type) override;
        void NotifyCollision(const GameObject& other) override;
};

#endif