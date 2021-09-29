#include "engine/Mat.h"
#include <cmath>
#include <iostream>

namespace mat {

// ---Rect
Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

Rect::~Rect() {}

Rect Rect::operator+(const Vec2& v) {
    return Rect(x+v.x, y-v.y, 0.0f, 0.0f);
}

Vec2 Rect::Center() const {
    Vec2 v;
    v.x = x + w/2;
    v.y = y + h/2;
    return v;
}

void Rect::Centralize(const Rect& r) {
    auto center = r.Center();
    this->x = center.x - this->w/2;
    this->y = center.y - this->h/2;
}

void Rect::Centralize(const Vec2& v) {
    this->x = v.x - this->w/2;
    this->y = v.y - this->h/2;
}

bool Rect::Contains(const Vec2& v) const {
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

Vec2 Vec2::operator+(const Vec2& v) {
    return Vec2(x+v.x,y+v.y);
}

Vec2& Vec2::operator+=(const Vec2& v) {
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vec2 Vec2::operator-(const Vec2& v) {
    return Vec2(x-v.x, y-v.y);
}

Vec2& Vec2::operator-=(const Vec2& v) {
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

Vec2 Vec2::operator*(const float& num) {
    return Vec2(x*num, y*num);
}

Vec2& Vec2::operator*=(const float& num) {
    this->x *= num;
    this->y *= num;
    return *this;
}

// Clockwise angle.
float Vec2::Angle() const {
    // https://stackoverflow.com/questions/1311049/how-to-map-atan2-to-degrees-0-360
    // https://stackoverflow.com/questions/14066933/direct-way-of-computing-clockwise-angle-between-2-vectors
    float dot = Dot(this->Normalized(), Vec2(1, 0)); 
    float det = Det(this->Normalized(), Vec2(1, 0)); 
    float result = (float)atan2(det, dot);
    result = (float)fmod((result+2*PI), 2*PI);
    return result; 
}

float Vec2::AngleToPoint(const Vec2& v) const {
    Vec2 temp = Vec2(v.x - x, v.y - y);    // line
    return temp.Angle(); 
}

float Vec2::DistanceTo(const Vec2& v) const {
    Vec2 temp(v.x - x, v.y - y);
    return temp.Length();
}

float Vec2::Dot(const Vec2& v) const {
    return Dot(*this, v);
}

bool Vec2::IsNormalized() const {
    // return (std::abs(x) <= 1.001 && std::abs(y) <= 1.001);    // ? How to properly handle fp imprecision? 
    return std::abs(this->Length() - 1.0f) < 0.01f;
}

float Vec2::Length() const {
    return (float)sqrt(x*x + y*y);
}

Vec2 Vec2::Normalized() const {
    return Vec2(x/Length(), y/Length());
}

Vec2 Vec2::Rotated(const float& rad) const {
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
float Deg2Rad(const float& deg) {
    return PI*deg/180;
}

float Rad2Deg(const float& rad) {
    return 180*rad/PI;
}

} // end of namespace mat