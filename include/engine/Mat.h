#ifndef __MAT_H__
#define __MAT_H__

#include <cmath>
namespace mat {

const float PI = 3.141593f;
const float EPS = 1e-6f;

class Vec2;

class Rect {
    public:
        float x, y, w, h;
        
        Rect(float = 0.0f, float = 0.0f, float = 0.0f, float = 0.0f);
        ~Rect();  

        // Rect operator+(const Vec2& v);
        Vec2 GetPos();
        void SetPos(const Vec2& v);
        void SetPos(const float& x, const float& y);

        /**
         * Returns the rectangle's central point. 
         */
        Vec2 Center() const;
        void Centralize(const Rect& r);
        void Centralize(const Vec2& v);
        /**
         * Check if @p v is inside of the rectangle.
         */
        bool Contains(const Vec2& v) const;
        float CentersDistance(const Rect& r); 
};

class Vec2 {
    public:
        float x, y;
        
        Vec2(float = 0.0f, float = 0.0f);
        Vec2(const Vec2& v);
        ~Vec2();

        Vec2& operator=(const Vec2& v);
        bool operator==(const Vec2& v) = delete;
        
        Vec2 operator+(const Vec2& v) const;
        Vec2& operator+=(const Vec2& v); 
        
        Vec2 operator-(const Vec2& v) const;
        Vec2& operator-=(const Vec2& v);
        
        Vec2 operator*(const float& x) const;
        Vec2& operator*=(const float& x);

        /**
         * Returns the angle between this vector and positive X axis (1, 0).
         */
        float Angle() const;
        /**
         * Returns the angle formed by the line connecting the two points and X axis.
         */
        float AngleToPoint(const Vec2& v) const;
        /**
         * Distance to another point.
         */
        float DistanceTo(const Vec2& v) const;
        /**
         * Dot product of two vectors (produto interno).
         */
        float Dot(const Vec2& v) const;
        /**
         * Checks if vector is normalized. Considers epsilon = 0.01
         */ 
        bool IsNormalized() const;
        /** 
         * Magnitude of the vector.
         */
        float Length() const;
        /**
         * Normalize the vector.
         */
        Vec2 Normalized() const;
        /**
         * Rotates the vector by the amount specified (radians).
         */
        Vec2 Rotated(const float& rad) const;
        
        static float Det(const Vec2& v1, const Vec2& v2);
        
        static float Dot(const Vec2& v1, const Vec2& v2);
};

// ---Functions
inline float Deg2Rad(const float& deg) {
    return PI*deg/180;
}

inline float Rad2Deg(const float& rad) {
    return 180*rad/PI;
}

inline float randf() {
    return (float)rand()/(float)RAND_MAX;
}

/** 
 * Distance of two rectangles' central point.
*/
inline float CentersDistance(const Rect& r1, const Rect& r2) {
    Vec2 diff = r1.Center() - r2.Center();
    return diff.Length();
}

inline Vec2 Rotate(const Vec2& v, const float& angle) {
    float cs = cosf(angle), sn = sinf(angle);
    return Vec2(v.x*cs - v.y*sn, v.x*sn + v.y*cs);
}

static inline Vec2 Normalize(const Vec2& v) {
    return v * (1.0f / v.Length());
}

} // end Mat;

#endif