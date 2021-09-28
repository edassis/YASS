#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "engine/Mat.h"
#include <memory>
// #include "engine/GameObject.h"

class GameObject;

class Camera {
    private:

    public:
        std::weak_ptr<GameObject> focus; 
        mat::Vec2 pos;
        mat::Vec2 speed;

        Camera();
        ~Camera();

        void Follow(std::weak_ptr<GameObject> newFocus);
        void Unfollow();
        void Update(float dt);
};

#endif