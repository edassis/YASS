#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <iostream>

class GameObject;

class Component {
    protected:
        GameObject& associated;
        
    public:
        Component(GameObject& associated) : associated(associated) {};
        virtual ~Component() {};

        virtual void Start() {};

        virtual void Update(float dt) {};
        virtual void Render() {};
        virtual bool Is(std::string type) =0;
        virtual void NotifyCollision(const GameObject& other) {};
};

#endif