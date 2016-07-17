// 
// material.h
//

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <iostream>
#include "geometry.h"

class Material {

public:

    Material () {}

    Material (float dr, float dg, float db,
              float sr, float sg, float sb,
              float pE,
              float ir, float ig, float ib)
    {
        Vector d(dr, dg, db);
        Vector s(sr, sg, sb);
        Vector i(ir, ig, ib);
        diffuse = d; specular = s; ideal = i;
        phongE = pE;
    }

    Material& operator=(const Material& m) {
        diffuse = m.diffuse;
        specular = m.specular;
        ideal = m.ideal;
        phongE = m.phongE;

        return *this;
    }

    Vector phongShading(const Vector& l, const Vector& v, 
                        const Vector& n, Vector& color) const;


    // Material data
    Vector diffuse;
    Vector specular;
    Vector ideal;
    float phongE;

};

#endif
