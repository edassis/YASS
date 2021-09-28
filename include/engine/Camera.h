#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "engine/Mat.h"
#include <memory>
// #include "engine/GameObject.h"

class GameObject;

class Camera {
    private:
        std::weak_ptr<GameObject> focus; 
        mat::Vec2 pos;
        mat::Vec2 speed;

    public:
        Camera();
        ~Camera();

        void Follow(std::weak_ptr<GameObject> newFocus);
        void Unfollow();
        void Update(float dt);

        mat::Vec2 GetPos();
        mat::Vec2 GetSpeed();
};

#endif