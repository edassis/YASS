#ifndef __MAT_H__
#define __MAT_H__

namespace mat {

const float PI = 3.141593f;

class Vec2;

class Rect {
    public:
        float x, y, w, h;
        
        Rect(float = 0.0f, float = 0.0f, float = 0.0f, float = 0.0f);
        ~Rect();  

        Rect operator+(const Vec2& v);

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
        /** 
         * Distance of two rectangles' central point.
         */
        static float DistanceFromCenters(Rect& r1, Rect& r2);
};

class Vec2 {
    public:
        float x, y;
        
        Vec2(float = 0.0f, float = 0.0f);
        Vec2(const Vec2& v);
        ~Vec2();

        Vec2& operator=(const Vec2& v);
        Vec2 operator+(const Vec2& v);
        Vec2& operator+=(const Vec2& v);
        Vec2 operator-(const Vec2& v);
        Vec2& operator-=(const Vec2& v);
        bool operator==(const Vec2& v) = delete;
        
        Vec2 operator*(const float& x);
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

float Deg2Rad(const float& deg);
float Rad2Deg(const float& rad);

} // end Mat;

#endif