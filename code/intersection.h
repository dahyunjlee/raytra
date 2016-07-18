// 
// intersection.h
//

#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "geometry.h"

class Intersection {
public:

    Intersection() {t = INFINITY; Point p; Vector n; id = -1;}

    // Intersection public data
    //
    Point p;
    Vector n;
    double t;
    int id;

};

#endif
