// 
// intersection.h
//

#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "geometry.h"

class Intersection {
public:

    Intersection() {t = INFINITY; Point p; Vector n;}

    // Intersection public data
    //
    Point p;
    Vector n;
    double t;

};

#endif
