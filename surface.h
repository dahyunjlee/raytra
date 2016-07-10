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

class Triangle : public Surface {

public:
    Triangle (Point p_1, Point p_2, Point p_3)
        :p1(p_1), p2(p_2), p3(p_3)
    {
        Vector u = p2 - p1;
        Vector v = p3 - p1;
        norm = cross(u, v);
    }

    virtual bool intersect (const Ray& ray, Intersection& it);

private:
    Point p1, p2, p3;
    double u, v, w; // barycentric coordinates
    Vector norm;

};


#endif
