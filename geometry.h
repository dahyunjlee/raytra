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

    // Cross and Dot Products
    //
    Vector cross(const Vector& u, const Vector& v) {
        return Vector(u.y*v.z - u.z*v.y, u.z*v.x - u.x*v.z, u.x*v.y - u.y*v.x); }

    double dot(const Vector& u, const Vector& v) {
        return (


    // Vector public data
    //
    double x, y, z;

};

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



    // Point public data
    //
    double x, y, z;

}

#endif
