#ifndef __MAT_H__
#define __MAT_H__

namespace mat {

const float PI = 3.141593;

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
        Vec2 center();
        /**
         * Check if @p v is inside of the rectangle.
         */
        bool contains(const Vec2& v);
        /** 
         * Distance of two rectangles' central point.
         */
        static float distance_from_centers(Rect& r1, Rect& r2);
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
        float angle();
        /**
         * Returns the angle formed by the line connecting the two points and X axis.
         */
        float angle_to_point(const Vec2& v);
        /**
         * Distance to another point.
         */
        float distance_to(const Vec2& v);
        /**
         * Dot product of two vectors (produto interno).
         */
        float dot(const Vec2& v);
        /**
         * Checks if vector is normalized. Considers epsilon = 0.01
         */ 
        bool is_normalized();
        /** 
         * Magnitude of the vector.
         */
        float length();
        /**
         * Normalize the vector.
         */
        Vec2 normalized();
        /**
         * Rotates the vector by the amount specified (radians).
         */
        Vec2 rotated(const float rad);
};

float deg2rad(const float deg);
float rad2deg(const float rad);
float det(const Vec2& v1, const Vec2& v2);
float dot(const Vec2& v1, const Vec2& v2);

} // end Mat;

#endif