// 
// camera.cc
//

#include "camera.h"

// Initialize camera
// Called while parsing scene file
//
void Camera::init (Point pos, Vector dir, double d, 
                   double iw, double ih, int pw, int ph)
{
    eye = pos;
    w = ((-1)*dir).normalize();

    focal_length = d;

    image_width = iw;
    image_height = ih;

    pwidth = pw;
    pheight = ph;

    Vector up (0., 1., 0.);
    u = cross (up, w);
    v = cross (w, u);

    u.normalize();
    v.normalize();

    // set up image
    try
    {
        pixelBuffer.resizeErase(pheight, pwidth);
    }
    catch (const std::exception& exc) {
        std::cerr << exc.what() << std::endl;
        return;
    }


}

// Generate ray for given pixel
//
Ray Camera::generateRay (const double i, const double j)
{

    // get u and v values
    //
    double l = -image_width/2.0;  double r = image_width/2.0;
    double b = -image_height/2.0; double t = image_height/2.0;

    double uu = l + (r - l) * (i + .5) / pwidth;
    double vv = t + (b - t) * (j + .5) / pheight;

    Vector dir = -focal_length * w + uu*u + vv*v;

    Ray ray (eye, dir);

    return ray;
}

void Camera::renderScene (std::vector<Surface *>& surfaces)
{
    std::cout << "rendering" << std::endl;

    Vector rgb(0., 0., 0.);
    // for every pixel
    for (int j = 0; j < pheight; ++j) {
        for (int i = 0; i < pwidth; ++i) {

            // color calculations
            Ray ray = generateRay(i, j);
            Intersection foundIntersection;

            for (int surfnum = 0; surfnum < surfaces.size(); ++surfnum) {
                Surface *surf = surfaces[surfnum];
                Intersection i;
                if (surf->intersect(ray, i)) {
                    if (i.t > 0.0001 && i.t < foundIntersection.t)
                        foundIntersection = i;
                    rgb.x = 1;
                } else {
                    rgb.x = rgb.y = rgb.z = 0;
                }
            }
            setPixel (i, j, rgb.x, rgb.y, rgb.z);
        }
    }
}

void Camera::writeImage (const char *sceneFile)
{
    std::cout<<"write image"<<std::endl;
    //EXR
    try
    {
        RgbaOutputFile file (sceneFile, pwidth, pheight, WRITE_RGBA);
        file.setFrameBuffer (&pixelBuffer[0][0], 1, pwidth);
        file.writePixels (pheight);
    }
    catch (const std::exception& exc)
    {
        std::cerr << exc.what() << std::endl;
        return;
    }
}
