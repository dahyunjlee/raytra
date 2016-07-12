// 
// surface.cc
//

#include "surface.h"

bool Sphere::intersect(const Ray& ray, Intersection& it) {

    // terms used often in equation
    Vector v (ray.o - this->o);
    double d_dot_d = dot(ray.d, ray.d);

    // discriminant
    double dis_1 = dot(ray.d, v);
    dis_1 *= dis_1;
    
    double dis_2 = dot(v, v) - (this->r * this->r);
    dis_2 *= d_dot_d;

    double dis = dis_1 - dis_2;

    if (dis>=0) {
        if (dis==0)
            it.t = dot((-1)*ray.d, v) / d_dot_d;
        else
            it.t = (dot((-1)*ray.d, v) - sqrtf(dis)) / d_dot_d;

        it.p = ray.o + it.t * ray.d;
        it.n = (it.p - o).normalize();
        return true;
    }
    return false;
}

bool Triangle::intersect(const Ray& ray, Intersection& it) {

    // area of triangle
    //
    double area = norm.length();
    area /= 2;

    Point o = ray.o;
    Vector d = ray.d;
    Vector n = norm.normalize();

    // if plane and ray are parallel
    double d_dot_n = dot(d, n);
    if (d_dot_n == 0)
        return false;

    // Distance from ray origin to plane
    double t = dot(p1-o, n)/d_dot_n;
    
    // if triangle is behind ray
    if (t < 0) 
        return false;

    // Point p where ray intersects plane
    Point p = o + (t * d);

    // Inside-outside test
    // Vector perpendicular to triangle plane (!normal)
    Vector c; 
    c = cross(p2-p1, p-p1);
    if (dot (c, n) < 0)
        return false;

    c = cross(p3-p2, p-p2);
//    if ((u = dot(c, n)) < 0)
    if ((dot(c, n)) <= 0)
        return false;

    c = cross(p1-p3, p-p3);
//    if ((v = dot(c, n)) < 0)
    if ((dot(c, n)) <= 0)
        return false;

//    u /= area;
//    v /= area;
//    w = 1 - u - v;

    it.t = t;
    it.p = p;
    it.n = n;
    return true;

}
