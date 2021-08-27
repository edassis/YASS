#include "engine/Mat.h"
#include <cmath>

using namespace std;
using namespace mat;

// ---Rect
Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

Rect::~Rect() {}

Rect& Rect::operator+(const Vec2& v) {
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vec2 Rect::center() {
    Vec2 v;
    v.x = x + w/2;
    v.y = y + h/2;
    return v;
}

bool Rect::contains(const Vec2& v) {
    return (v.x > x && v.x < x+w) && (v.y > y && v.y < y+h); 
}

float Rect::distance_from_centers(Rect& r1, Rect& r2) {
    Vec2 diff = r1.center() - r2.center();
    return diff.length();
}

// ---Vector
Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2::Vec2(const Vec2& v) : Vec2(v.x, v.y) {}

Vec2::~Vec2() {}

Vec2& Vec2::operator=(const Vec2& v) {
    if(this == &v) return *this;

    this->x = v.x;
    this->y = v.y;
    return *this;
}

// * FP imprecision.
// bool Vec2::operator==(const Vec2& v) {
//     return (x == v.x) && (y == v.y);
// }

Vec2& Vec2::operator+(const Vec2& v) {
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vec2& Vec2::operator-(const Vec2& v) {
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

Vec2& Vec2::operator*(const int num) {
    this->x *= num;
    this->y *= num;
    return *this;
}

float Vec2::angle() {
    float dot = mat::dot(this->normalized(), Vec2(1, 0)); 
    float det = mat::det(this->normalized(), Vec2(1, 0)); 

    return atan2(det, dot); 
}

float Vec2::angle_to_point(const Vec2& v) {
    Vec2 temp = Vec2(v.x - x, v.y - y).normalized();    // line

    float dot = mat::dot(temp, Vec2(1, 0)); 
    float det = mat::det(temp, Vec2(1, 0)); 
    
    return atan2(det, dot); 
}

float Vec2::distance_to(const Vec2& v) {
    Vec2 temp(v.x - x, v.y - y);
    return temp.length();
}

float Vec2::dot(const Vec2& v) {
    return x*v.x + y*v.y;
}

bool Vec2::is_normalized() {
    return (abs(x) <= 1.01 && abs(y) <= 1.01);    // ? How to properly handle fp imprecision? 
}

float Vec2::length() {
    return sqrt(x*x + y*y);
}

Vec2 Vec2::normalized() {
    return Vec2(x/length(), y/length());
}

Vec2 Vec2::rotated(const float rad) {
    float x1 = x*cos(rad) - y*sin(rad);
    float y1 = y*cos(rad) + x*sin(rad);
    return Vec2(x1, y1);
}


// ---Functions
float mat::deg2rad(const float deg) {
    return mat::PI*deg/180;
}

float mat::rad2deg(const float rad) {
    return 180*rad/mat::PI;
}

float mat::det(const Vec2& v1, const Vec2& v2) {
    return v1.x*v2.y - v1.y*v2.x;   // det = x1*y2 - y1*x2
}

float mat::dot(const Vec2& v1, const Vec2& v2) {
    return v1.x*v2.x + v1.y*v2.y;   // dot = x1*x2 + y1*y2
}