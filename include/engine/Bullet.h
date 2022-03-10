#ifndef __BULLET_H__
#define __BULLET_H__

#include "engine/Component.h"
#include "engine/Mat.h"
#include <iostream>

class GameObject;

class Bullet : public Component {
    private:
        mat::Vec2 speed;
        float distanceLeft;
        int damage;
        bool targetsPlayer;
    
    public:
        Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string spritePath, int frameCount = 1, float frameTime = 0.0, bool targetsPlayer = true);

        int GetDamage() const;
        bool IsTargetPlayer() const;

        void Update(float dt) override;
        void Render() override;
        bool Is(std::string type) override;
        void NotifyCollision(const GameObject& other) override;
};

#endif
