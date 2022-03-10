#include "engine/Mat.h"
#include <cmath>
#include <iostream>

namespace mat {

// ---Rect
Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

Rect::~Rect() {}

Vec2 Rect::GetPos() {
    return Vec2(x, y);
}

void Rect::SetPos(const Vec2& v) {
    x = v.x;
    y = v.y;
}

void Rect::SetPos(const float& x, const float& y) {
    this->x = x;
    this->y = y;
}

Vec2 Rect::Center() const {
    Vec2 v;
    v.x = x + w/2;
    v.y = y + h/2;
    return v;
}

void Rect::Centralize(const Rect& r) {
    if(std::abs(w) < 0.1f || std::abs(h) < 0.1f) {
        std::cout << "Warning! Rect::Centralize() called with width/height = 0.0f." << std::endl;
        return;
    }
    auto center = r.Center();
    this->x = center.x - this->w/2;
    this->y = center.y - this->h/2;
}

void Rect::Centralize(const Vec2& v) {
    if(std::abs(w) < 0.1f || std::abs(h) < 0.1f) {
        std::cout << "Warning! Rect::Centralize() called with width/height = 0.0f." << std::endl;
        return;
    } 
    this->x = v.x - this->w/2;
    this->y = v.y - this->h/2;
}

bool Rect::Contains(const Vec2& v) const {
    if(std::abs(w) < 0.1f || std::abs(h) < 0.1f) {
        std::cout << "Warning! Rect::Contains() called with width/height = 0.0f." << std::endl;
        return false;
    }
    return (v.x > x && v.x < x+w) && (v.y > y && v.y < y+h); 
}

float Rect::CentersDistance(const Rect& r) {
    return mat::CentersDistance(*this, r);
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

Vec2 Vec2::operator+(const Vec2& v) const {
    return Vec2(x+v.x,y+v.y);
}

Vec2& Vec2::operator+=(const Vec2& v) {
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vec2 Vec2::operator-(const Vec2& v) const {
    return Vec2(x-v.x, y-v.y);
}

Vec2& Vec2::operator-=(const Vec2& v) {
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

Vec2 Vec2::operator*(const float& num) const {
    return Vec2(x*num, y*num);
}

Vec2& Vec2::operator*=(const float& num) {
    this->x *= num;
    this->y *= num;
    return *this;
}

// Clockwise angle.
// Interval -> [-PI, PI]
float Vec2::Angle() const {
    // https://stackoverflow.com/questions/1311049/how-to-map-atan2-to-degrees-0-360
    // https://stackoverflow.com/questions/14066933/direct-way-of-computing-clockwise-angle-between-2-vectors
    // float dot = Dot(this->Normalized(), Vec2(1, 0)); 
    // float det = Det(this->Normalized(), Vec2(1, 0)); 
    // float result = (float)atan2(det, dot);
    float result = (float)atan2(y, x);
    // result = (float)fmod((result+2*PI), 2*PI);
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
    return std::abs(this->Length() - 1.0f) < EPS;
}

float Vec2::Length() const {
    return (float)sqrt(x*x + y*y);
}

Vec2 Vec2::Normalized() const {
    return Normalize(*this);
}

Vec2 Vec2::Rotated(const float& rad) const {
    return Rotate(*this, rad);
}

float Vec2::Det(const Vec2& v1, const Vec2& v2) {
    return v1.x*v2.y - v1.y*v2.x;   // det = x1*y2 - y1*x2
}

float Vec2::Dot(const Vec2& v1, const Vec2& v2) {
    return v1.x*v2.x + v1.y*v2.y;   // dot = x1*x2 + y1*y2
}

} // end of namespace mat