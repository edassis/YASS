
#ifndef __PENGUINCANNON_H_
#define __PENGUINCANNON_H_

#include "engine/Component.h"
#include "engine/GameObject.h"
#include "engine/Mat.h"
#include <memory>

class PenguinCannon : public Component {
    private:
        std::weak_ptr<GameObject> wpBody;
        // float angle;

    public:
        PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
        ~PenguinCannon();
        
        void Shoot();
       
        void Update(float dt) override;
        void Render() override;
        bool Is(std::string type) override;
        void NotifyCollision(const GameObject& other) override;
};

#endif
