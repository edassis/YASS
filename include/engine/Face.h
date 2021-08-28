#ifndef __FACE_H__
#define __FACE_H__

#include "engine/Component.h"

class Face : public Component {
    private:
        int hitpoints;
    public:
        Face(GameObject& associated);
        
        void Damage(int damage);
        
        /* Component */
        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;
};

#endif