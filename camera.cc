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

// Color calculations for given pixel
//
Vector Camera::setColor (Ray& ray, Light* light, Intersection& it, Surface* s)
{
    Vector l = (dynamic_cast<PLight*>(light)->pos - it.p).normalize();
    Vector v = (-1.0 * ray.d).normalize();
    Vector h = (v + l).normalize();

    float phong = s->material->phongE;

    double max1 = fmax(0., dot(it.n, l));
    double max2 = pow(fmax(0., dot(it.n, h)), phong);

    float r = (s -> material->diffuse[0]) * max1
            + (s -> material->specular[0]) * max2;
    float g = (s -> material->diffuse[1]) * max1
            + (s -> material->specular[1]) * max2;
    float b = (s -> material->diffuse[2]) * max1
            + (s -> material->specular[2]) * max2;

    return Vector(r, g, b);
}

// Iterate through each pixel
//
void Camera::renderScene (std::vector<Light *>& lights,
                          std::vector<Surface *>& surfaces)
{
    std::cout << "rendering" << std::endl;

    // only one light for now
    Light* light = lights[0];
    Vector rgb(0., 0., 0.);
    bool itfound;
    
    // for every pixel
    for (int j = 0; j < pheight; ++j) {
        for (int i = 0; i < pwidth; ++i) {
            itfound = false;

            // color calculations
            Ray ray = generateRay(i, j);
            Intersection foundIntersection;
            Surface *foundSurf;

            for (int surfnum = 0; surfnum < surfaces.size(); ++surfnum) {
                Surface *surf = surfaces[surfnum];
                Intersection i;
                if (surf->intersect(ray, i)) {
                    itfound = true;
                    if (i.t > 0.0001 && i.t < foundIntersection.t) {
                        foundIntersection = i;
                        foundSurf = surf;
                    }
                }
            }
            if (itfound)
                rgb = setColor (ray, light, foundIntersection, foundSurf);
            else 
                // default color
                rgb.x = rgb.y = rgb.z = 0;

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
