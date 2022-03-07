#ifndef __PENGUINBODY_H_
#define __PENGUINBODY_H_

#include "engine/Component.h"
#include "engine/Mat.h"

class PenguinBody : public Component {
    private:
        std::weak_ptr<GameObject> wpCannon;
        mat::Vec2 speed;
        int linearSpeed;
        float angle;
        int hp;

    public:
        PenguinBody(GameObject& associated);
        ~PenguinBody();
        
        // Component
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);

        PenguinBody* player;
};

#endif
