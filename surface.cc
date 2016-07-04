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
    
    double dis_2 = dot(ray.d, v);
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
