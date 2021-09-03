#ifndef __MAT_H__
#define __MAT_H__

namespace mat {

const float PI = 3.141593f;

class Vec2;

class Rect {
    public:
        float x, y, w, h;
        
        Rect(float = 0.0, float = 0.0, float = 0.0, float = 0.0);
        ~Rect();  

        Rect& operator+(const Vec2& v);

        /**
         * Returns the rectangle's central point. 
         */
        Vec2 Center();
        /**
         * Check if @p v is inside of the rectangle.
         */
        bool Contains(const Vec2& v);
        /** 
         * Distance of two rectangles' central point.
         */
        static float DistanceFromCenters(Rect& r1, Rect& r2);
};

class Vec2 {
    public:
        float x, y;
        
        Vec2(float = 0.0, float = 0.0);
        Vec2(const Vec2& v);
        ~Vec2();

        Vec2& operator=(const Vec2& v);
        // bool operator==(const Vec2& v);
        Vec2& operator+(const Vec2& v);
        Vec2& operator-(const Vec2& v);
        // Vec2& operator*(const Vec2& v);
        Vec2& operator*(const int x);

        /**
         * Returns the angle between this vector and positive X axis (1, 0).
         */
        float Angle();
        /**
         * Returns the angle formed by the line connecting the two points and X axis.
         */
        float AngleToPoint(const Vec2& v);
        /**
         * Distance to another point.
         */
        float DistanceTo(const Vec2& v);
        /**
         * Dot product of two vectors (produto interno).
         */
        float Dot(const Vec2& v);
        /**
         * Checks if vector is normalized. Considers epsilon = 0.01
         */ 
        bool IsNormalized();
        /** 
         * Magnitude of the vector.
         */
        float Length();
        /**
         * Normalize the vector.
         */
        Vec2 Normalized();
        /**
         * Rotates the vector by the amount specified (radians).
         */
        Vec2 Rotated(const float rad);
        
        static float Det(const Vec2& v1, const Vec2& v2);
        
        static float Dot(const Vec2& v1, const Vec2& v2);
};

float Deg2Rad(const float deg);
float Rad2Deg(const float rad);

} // end Mat;

#endif