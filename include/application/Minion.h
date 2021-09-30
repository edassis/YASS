#ifndef __MINION_H__
#define __MINION_H__

#include "engine/Component.h"
#include "engine/Mat.h"
#include <memory>

class Minion : public Component {
    private:
        std::weak_ptr<GameObject> alienCenter;
        float arcDeg;  // Degrees.

    public:
        Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0.0f);

        void Update(float dt) override;
        void Render() override;
        bool Is(std::string type) override;

        void Shoot(mat::Vec2 target);
};

#endif