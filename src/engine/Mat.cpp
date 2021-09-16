#include "engine/Mat.h"
#include <cmath>

using namespace mat;

// ---Rect
Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

Rect::~Rect() {}

Rect& Rect::operator+(const Vec2& v) {
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vec2 Rect::Center() {
    Vec2 v;
    v.x = x + w/2;
    v.y = y + h/2;
    return v;
}

bool Rect::Contains(const Vec2& v) {
    return (v.x > x && v.x < x+w) && (v.y > y && v.y < y+h); 
}

float Rect::DistanceFromCenters(Rect& r1, Rect& r2) {
    Vec2 diff = r1.Center() - r2.Center();
    return diff.Length();
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

Vec2& Vec2::operator+=(const Vec2& v) {
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vec2& Vec2::operator-(const Vec2& v) {
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& v) {
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

Vec2& Vec2::operator*(const int num) {
    this->x *= (float)num;
    this->y *= (float)num;
    return *this;
}

float Vec2::Angle() {
    float dot = Dot(this->Normalized(), Vec2(1, 0)); 
    float det = Det(this->Normalized(), Vec2(1, 0)); 

    return (float)atan2(det, dot); 
}

float Vec2::AngleToPoint(const Vec2& v) {
    Vec2 temp = Vec2(v.x - x, v.y - y);    // line
    return temp.Angle(); 
}

float Vec2::DistanceTo(const Vec2& v) {
    Vec2 temp(v.x - x, v.y - y);
    return temp.Length();
}

float Vec2::Dot(const Vec2& v) {
    return Dot(*this, v);
}

bool Vec2::IsNormalized() {
    return (std::abs(x) <= 1.001 && std::abs(y) <= 1.001);    // ? How to properly handle fp imprecision? 
}

float Vec2::Length() {
    return (float)sqrt(x*x + y*y);
}

Vec2 Vec2::Normalized() {
    return Vec2(x/Length(), y/Length());
}

Vec2 Vec2::Rotated(const float rad) {
    float x1 = float(x*cos(rad) - y*sin(rad));
    float y1 = float(y*cos(rad) + x*sin(rad));
    return Vec2(x1, y1);
}

float Vec2::Det(const Vec2& v1, const Vec2& v2) {
    return v1.x*v2.y - v1.y*v2.x;   // det = x1*y2 - y1*x2
}

float Vec2::Dot(const Vec2& v1, const Vec2& v2) {
    return v1.x*v2.x + v1.y*v2.y;   // dot = x1*x2 + y1*y2
}

// ---Functions
float mat::Deg2Rad(const float deg) {
    return mat::PI*deg/180;
}

float mat::Rad2Deg(const float rad) {
    return 180*rad/mat::PI;
}
