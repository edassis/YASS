#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "engine/Mat.h"
#include <iostream>
#include <vector>

using std::vector;
using std::string;

class Component;

class GameObject {
    private:
        vector<Component*> components;
        bool isDead;

    public:
        Rect box;

        GameObject();
        ~GameObject();

        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(string type);
};

#endif