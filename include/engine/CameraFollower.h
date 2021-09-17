#ifndef __CAMERAFOLLOWER_H__
#define __CAMERAFOLLOWER_H__

#include "engine/Component.h"

class CameraFollower : public Component {
    public:
        CameraFollower(GameObject& go);
        ~CameraFollower();

        /* Component */
        void Update(float dt) override;
        void Render() override;
        bool Is(std::string type) override;
};

#endif