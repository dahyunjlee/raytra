// 
// bbox.h
//

#ifndef BBOX_H_
#define BBOX_H_

#include "geometry.h"
#include "ray.h"
#include "intersection.h"

const double eps = 0.001;

class BBox {

public:

    BBox() {
        min = Point ( INFINITY,  INFINITY,  INFINITY);
        max = Point (-INFINITY, -INFINITY, -INFINITY);
        id = -1;
    }

    BBox (const BBox &b) {
        min = b.min;
        max = b.max;
        id = b.id;
    }

    BBox (const Point &p) :min(p), max(p), id(-1) {}

    BBox (const Point &p1, const Point &p2, const int id_ = -1) {
        min = Point(fmin(p1.x, p2.x), fmin(p1.y, p2.y), fmin(p1.z, p2.z));
        max = Point(fmax(p1.x, p2.x), fmin(p1.y, p2.y), fmax(p1.z, p2.z));
        id = id_;
    }

    void expand (const double delta) {
        min -= Vector (delta, delta, delta);
        max += Vector (delta, delta, delta);
    }

    friend BBox Union (const BBox &b1, const BBox &b2);
    friend BBox Union (const BBox &b1, const Point &p);
    
    bool intersect(const Ray &ray, Intersection &it);


    // bbox data
    //
    Point min, max;
    int id;

};

#endif
