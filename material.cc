// 
// material.cc
//

#include "material.h"

Vector Material::phongShading(
        const Vector& l, // direction from intersection to light
        const Vector& v, // direction toward camera
        const Vector& n, // normal at intersection
        Vector& color) const // intensity of light source
{

    //std::cout<<"ph"<<std::endl;
    Vector h = (v + l).normalize();
    
    double max1 = fmax(0., dot(n, l));
    double max2 = pow(fmax(0., dot(n, h)), phongE);

    float r = diffuse[0] * max1 + specular[0] * max2;
    float g = diffuse[1] * max1 + specular[1] * max2;
    float b = diffuse[2] * max1 + specular[2] * max2;

    r *= color[0];
    g *= color[1];
    b *= color[2];

    return Vector (r, g, b);
}
