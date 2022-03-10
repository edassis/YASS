#ifndef __PENGUINBODY_H_
#define __PENGUINBODY_H_

#include "engine/Component.h"
#include "engine/Mat.h"
#include <memory>

class PenguinBody : public Component {
    private:
        std::weak_ptr<GameObject> wpCannon;
        mat::Vec2 speed;
        int linearSpeed;
        // float angle;
        int hp;

    public:
        // PenguinBody* player;
        
        PenguinBody(GameObject& associated);
        ~PenguinBody();

        // Component
        void Start() override;
        void Update(float dt) override;
        void Render() override;
        bool Is(std::string type) override;
        void NotifyCollision(const GameObject& other) override;
};

#endif
