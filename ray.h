// 
// ray.h
//

#ifndef RAY_H_
#define RAY_H_

#include "geometry.h"

class Ray {

public:

    Ray() {}
    Ray(const Ray& r)
        : o(r.o), d(r.d) {}

    Ray& operator=(const Ray& r) {
        o = r.o; d = r.d; return *this; }

    // Ray Public data
    //
    Point o;
    Vector d;

}

#endif
