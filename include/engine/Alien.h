#ifndef __ALIEN_H__
#define __ALIEN_H__

#include "engine/Component.h"
#include "engine/Mat.h"
#include <string>
#include <vector>
#include <queue>
#include <memory>

class Alien : public Component {
    private:
        class Action {
            public:
                enum ActionType {MOVE, SHOOT};
                ActionType type;
                mat::Vec2 pos;

                Action(ActionType type, float x, float y);
        };

        int hp;
        mat::Vec2 speed;
        int nMinion;
        std::queue<Action> taskQueue;
        std::vector<std::weak_ptr<GameObject>> minionArray;

    public:
        Alien(GameObject& associated, int nMinion);
        ~Alien();

        void Start();
        /* Component */
        void Update(float dt) override;
        void Render() override;
        bool Is(std::string type) override;
};

#endif