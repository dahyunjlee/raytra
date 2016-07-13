// 
// camera.h
//

#ifndef CAMERA_H_
#define CAMERA_H_

#include <vector>
#include <cmath>
#include "ray.h"
#include "intersection.h"
#include "surface.h"
#include "light.h"

#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>

using namespace Imf;

class Camera {

public:

    void init (Point p, Vector dir, double d, double iw, double ih, int pw, int ph);

    Ray generateRay (const double i, const double j);

    Vector setColor (Ray& ray, std::vector<Light *>& lights,
                     std::vector<Surface *>& surfaces);

    void renderScene (std::vector<Light *>&lights,
                      std::vector<Surface *>& surfaces);

    void writeImage (const char *sceneFile);

    void setPixel (int pix_x, int pix_y, float r, float g, float b) {
        Rgba &px = pixelBuffer[pix_y][pix_x];
        px.r = r;
        px.g = g;
        px.b = b;
        px.a = 1.0;
    }

private:
    
    Point eye;
    Vector u; 
    Vector v;
    Vector w;

    double image_width;
    double image_height;
    double focal_length;
    int pwidth;
    int pheight;

    Array2D<Rgba> pixelBuffer;

};

#endif
