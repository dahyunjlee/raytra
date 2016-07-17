// 
// bbox.cc
//

#include "bbox.h"

BBox Union (const BBox &b1, const BBox &b2) {
    BBox b;
    b.min.x = fmin(b1.min.x, b2.min.x);
    b.min.y = fmin(b1.min.y, b2.min.y);
    b.min.z = fmin(b1.min.z, b2.min.z);
    b.max.x = fmax(b1.max.x, b2.max.x);
    b.max.y = fmax(b1.max.y, b2.max.y);
    b.max.z = fmax(b1.max.z, b2.max.z);
    return b;
}

BBox Union (const BBox &b1, const Point &p) {
    BBox b;
    b.min.x = fmin(b1.min.x, p.x);
    b.min.y = fmin(b1.min.y, p.y);
    b.min.z = fmin(b1.min.z, p.z);
    b.max.x = fmax(b1.max.x, p.x);
    b.max.y = fmax(b1.max.y, p.y);
    b.max.z = fmax(b1.max.z, p.z);
    return b;
}

bool BBox::intersect(const Ray &ray, Intersection &it) {
    
    Vector n;
    double d, txmin, txmax, tymin, tymax, tzmin, tzmax, tnear, tfar;

    if (ray.d.x == 0) {
        if (ray.o.x < min.x)
            txmin = txmax = INFINITY;
        else if (ray.o.x > max.x)
            txmin = txmax = -INFINITY;
        else {
            txmin = -INFINITY;
            txmax = INFINITY;
        }
    }
    else {
        d = 1/ray.d.z;  // sign matters to find intersection with nearer plane
        if (d >= 0) {
            txmin = d*(this->min.x - ray.o.x);
            txmax = d*(this->max.x - ray.o.x);
            tnear = txmin;
            n = Vector (-1, 0, 0);
        }
        else {
            txmin = d*(this->max.x - ray.o.x);
            txmax = d*(this->min.x - ray.o.x);
            tnear = txmin;
            n = Vector (1, 0, 0);
        }
    }

    if (ray.d.y == 0) {
        if (ray.o.y < min.y) 
            tymin = tymax = INFINITY;
        else if (ray.o.y > max.y)
            tymin = tymax = -INFINITY;
        else {
            tymin = -INFINITY;
            tymax = INFINITY;
        }
    }
    else {
        d = 1/ray.d.y;
        if (d >= 0) {
            tymin = d*(this->min.y - ray.o.y);
            tymax = d*(this->max.y - ray.o.y);
            if (tymin > tnear) {
                tnear = tymin;
                n = Vector (0, -1, 0);
            }
        }
        else {
            tymin = d*(this->max.y - ray.o.y);
            tymax = d*(this->max.x - ray.o.y);
            if (tymin > tnear) {
                tnear = tymin;
                n = Vector (0, 1, 0);
            }
        }
    }

    if (ray.d.z == 0) {
        if (ray.o.z < min.z)
            tzmin = tzmax = INFINITY;
        else if (ray.o.z > max.z)
            tzmin = tzmax = -INFINITY;
        else {
            tzmin = -INFINITY;
            tzmax = INFINITY;
        }
    }
    else {
        d = 1/ray.d.z;
        if (d >= 0) {
            tzmin = d*(this->min.z - ray.o.z);
            tzmax = d*(this->max.z - ray.o.z);
            if (tzmin > tnear) {
                tnear = tzmin;
                n = Vector (0, 0, -1);
            }
        }
        else {
            tzmin = d*(this->max.z - ray.o.z);
            tzmax = d*(this->min.z - ray.o.z);
            if (tzmin > tnear) {
                tnear = tzmin;
                n = Vector (0, 0, 1);
            }
        }
    }

    tfar = fmin (txmax, fmin (tymax, tzmax));

    if (tnear > tfar) return false;     // no intersection
    if (tfar < 0) return false;         // box behind ray

    it.t = tnear;
    it.p = ray.o + ray.d * tnear;
    it.n = n;

    return true;
}
