// 
// surface.h
//

#ifndef SURFACE_H_
#define SURFACE_H_

#include "ray.h"
#include "intersection.h"

class Surface {

public:
    virtual bool intersect (const Ray& ray, Intersection&) {return false;}

};

class Sphere : public Surface {

public:
    Sphere (Point oo, double rr) : o(oo), r(rr) {}
    Sphere (double x, double y, double z, double rr)
        : o(x, y, z), r(rr) {}

    virtual bool intersect (const Ray& ray, Intersection& it);

private:
    Point o;
    double r;
    
};

#endif
