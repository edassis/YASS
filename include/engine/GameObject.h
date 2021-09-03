#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "engine/Mat.h"
#include <iostream>
#include <vector>
#include <memory>

using std::vector;
using std::string;
using std::unique_ptr;
using std::shared_ptr;

using mat::Rect;

class Component;

class GameObject {
    private:
        vector<shared_ptr<Component>> components;
        bool isDead;
    public:
        Rect box;

        GameObject();
        ~GameObject();

        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(shared_ptr<Component> cpt);
        void RemoveComponent(Component& cpt);
        shared_ptr<Component> GetComponent(string type);
};

#endif