// 
// geometry.h
// basic geometry-- point, vector, etc
//

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <cmath>
#include <cassert>

class Vector {

public:

    Vector() {x = y = z = 0.;}

    Vector(double xx, double yy, double zz)
        : x(xx), y(yy), z(zz) {}

    Vector(const Vector& v)
        : x(v.x), y(v.y), z(v.z) {}

    Vector& operator=(const Vector& v) {
        x = v.x; y = v.y; z = v.z; return *this; }

    // Arithmetic Operators
    //
    Vector& operator+=(const Vector& v) {
        x += v.x; y += v.y; z += v.z; return *this; }

    Vector& operator-=(const Vector& v) {
        x -= v.x; y -= v.y; z -= v.z; return *this; }

    Vector& operator*=(const double d) {
        x *= d; y *= d; z *= d; return *this; }

    Vector& operator/=(const double d) {
        x /= d; y /= d; z /= d; return *this; }

    Vector operator+(const Vector& v) const {
        return Vector(x + v.x, y + v.y, z + v.z); }

    Vector operator-(const Vector& v) const {
        return Vector(x - v.x, y - v.y, z - v.z); }

    Vector operator/(double d) const {
        return Vector(x/d, y/d, z/d); }

    Vector operator*(double d) const {
        return Vector(x*d, y*d, z*d); }

    friend Vector operator*(double d, const Vector& v) {
        return Vector(v.x * d, v.y * d, v.z * d); }

    double& operator[] (const int i);
    double operator[] (const int i) const;

    // Cross and Dot Products
    //
    friend Vector cross(const Vector& u, const Vector& v) {
        return Vector(u.y*v.z - u.z*v.y, u.z*v.x - u.x*v.z, u.x*v.y - u.y*v.x); }

    friend double dot(const Vector& u, const Vector& v) {
        return (u.x*v.x + u.y*v.y + u.z*v.z); }

    // Other Functions
    //
    double length() const {
        return sqrtf (x*x + y*y + z*z); }

    // normalizes function
    Vector& normalize() {
        assert (! (x==0. && y==0. && z==0.));
        double l = this->length();
        x/=l; y/=l; z/=l;
        return *this; 
    }


    // Vector public data
    //
    double x, y, z;

};

inline double& Vector::operator[] (const int i) 
{
    assert (i >= 0 && i < 3);
    if (i == 0)
        return x;
    if (i == 1)
        return y;
    else
        return z;
}

inline double Vector::operator[] (const int i) const
{
    assert (i >= 0 && i < 3);
    if (i == 0)
        return x;
    if (i == 1)
        return y;
    else
        return z;
}

class Point {

public:

    Point() {x = y = z = 0.;}

    Point(double xx, double yy, double zz)
        : x(xx), y(yy), z(zz) {}

    Point(const Point& p)
        : x(p.x), y(p.y), z(p.z) {}

    Point& operator=(const Point& p) {
        x = p.x; y = p.y; z = p.z; return *this; }

    // Arithmetic Operators
    //
    Vector operator-(const Point& p) const {
        return Vector(x - p.x, y - p.y, z - p.z); }

    Point operator-(const Vector& v) const {
        return Point(x - v.x, y - v.y, z - v.z); }

    Point& operator-=(const Vector& v) {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }

    Point operator+(const Point& p) const {
        return Point(x + p.x, y + p.y, z + p.z); }

    Point operator+(const Vector& v) const {
        return Point(x + v.x, y + v.y, z + v.z); }

    friend Point operator+(const Vector& v, const Point& p) {
        return Point(v.x + p.x, v.y + p.y, v.z + p.z); }

    Point& operator+=(const Point& p) {
        x += p.x; y += p.y; z += p.z;
        return *this;
    }

    Point& operator+=(const Vector& v) {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }

    double& operator[] (const int i);
    double operator[] (const int i) const;

    friend double dot(const Point& p, const Vector& v) {
        return (p.x*v.x + p.y*v.y + p.z* v.z); }

    // Point public data
    //
    double x, y, z;

};

inline double& Point::operator[] (const int i)
{
    assert (i >= 0 && i < 3);
    if (i == 0)
        return x;
    if (i == 1)
        return y;
    else 
        return z;
}

inline double Point::operator[] (const int i) const
{
    assert (i >= 0 && i < 3);
    if (i == 0)
        return x;
    if (i == 1)
        return y;
    else
        return z;
}

#endif
