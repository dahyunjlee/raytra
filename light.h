// 
// light.h
//

#ifndef LIGHT_H_
#define LIGHT_H_

#include "geometry.h"

class Light {

public:
    virtual ~Light() {}

    Vector color;
    int type;

};

class PLight : public Light {

public:
    PLight () {}
    PLight (Point p, float r, float g, float b) {
        pos = p;
        color[0] = r;
        color[1] = g;
        color[2] = b;
        type = 1;
    }

    // Point light data
    Point pos;
};

#endif
