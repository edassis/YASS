#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "engine/Mat.h"

class Collision {
    public:
        static bool IsColliding(mat::Rect& a, mat::Rect& b, float angleOfA, float angleOfB);
};

#endif