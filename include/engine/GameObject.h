#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "engine/Mat.h"
#include <iostream>
#include <vector>
#include <memory>

class Component;

class GameObject {
    private:
        std::vector<std::shared_ptr<Component>> components;
        bool isDead;
    public:
        mat::Rect box;

        GameObject();
        ~GameObject();

        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(std::shared_ptr<Component> cpt);
        void RemoveComponent(Component& cpt);
        std::shared_ptr<Component> GetComponent(std::string type);
};

#endif