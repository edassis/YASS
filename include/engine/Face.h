#ifndef __FACE_H__
#define __FACE_H__

#include "engine/Component.h"

class Face : public Component {
    private:
        int hitpoints;
        bool dead;
    public:
        Face(GameObject& associated);
        
        void Damage(int damage);
        
        /* Component */
        void Update(float dt) override;
        void Render() override;
        bool Is(std::string type) override;
};

#endif