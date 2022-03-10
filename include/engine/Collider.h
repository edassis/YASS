#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "engine/Component.h"
#include "engine/Mat.h"

class GameObject;

class Collider: public Component {
    private:
        mat::Vec2 scale;
        mat::Vec2 offset;
        // float angle;

    public:
        // bool enableDebug;
        mat::Rect box;

        Collider(GameObject& associated, mat::Vec2 scale = {1,1}, mat::Vec2 offset = {0,0});
        ~Collider();

        void SetScale(mat::Vec2 scale);
        void SetOffset(mat::Vec2 offset);
        // void SetAngle(float angle);
        // float GetAngle();

        void Update(float dt) override;
        void Render() override;
        bool Is(std::string type) override;

        bool IsColliding(const mat::Rect& otherBox, const float& otherAngle) const;
        static bool IsColliding(const mat::Rect& a, const mat::Rect& b, const float& angleOfA, const float& angleOfB);
};

#endif