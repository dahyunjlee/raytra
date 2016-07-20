// 
// camera.cc
//

#include "camera.h"


#define MAX_LIMIT 10

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
Vector Camera::setColor (Ray& ray, std::vector<Light *>& lights,
                         std::vector<Surface *>& surfaces, 
                         int limit, BVHNode *root)

{
    limit++;
    Vector rgb(0., 0., 0.);
    Intersection it;
    Material *m = NULL;

    if (limit == MAX_LIMIT) 
        return rgb;


    if (root) {
        if (root->intersect(ray, it) && it.id != -1){
            m = surfaces[it.id]->material;
        }
    }
    else {
        // iterate through each surface for intersection
        for (int surfnum = 0; surfnum < surfaces.size(); ++surfnum) {
            Intersection i;
            Surface *surf = surfaces[surfnum];
            if (surf->intersect(ray, i)) {
                if (i.t > 0.0001 && i.t < it.t) {
                    it = i;
                    m = surf->material;
                }
            }
        }
    }

    if (m) {
        // Intersection info
        Point p = it.p;
        Vector n = it.n;

        // direction back toward camera
        Vector v = (-1.0 * ray.d).normalize();

        // iterate through each light
        for (int lnum = 0; lnum < lights.size(); ++lnum) {
            Light *light = lights[lnum];

            // if point light
            if (light->type == 1) {

                Vector l = (dynamic_cast<PLight*>(light)->pos - p);
                double dist = l.length();
                l.normalize();

                // cast Shadow ray
                Ray shadowRay = Ray(p, l);
                bool isShadow = false;

                if (root) {
                    if (root->shadowTest(shadowRay, it) && it.t < dist)
                        isShadow = true;
                }
                else {

                    for (int surfnum = 0; surfnum < surfaces.size(); ++surfnum) {
                        Intersection i;
                        Surface *s = surfaces[surfnum];
                        if (s->intersect(shadowRay, i)) {
                            if (i.t > 0.0001 && i.t < dist) 
                                isShadow = true;
                        }
                    }
                }

                if (!isShadow)
                    rgb += m -> phongShading (l, v, n, light->color);
            }

            // if Ambient light
            if (light->type == 2)  {
            }

            // if Area light
            if (light->type == 3) {
            }
        }

        if (m->ideal.length()) {
            Vector n = it.n;
            Vector rDir = ray.d - 2 * dot(ray.d, n) * n;
            Ray rRay = Ray (it.p, rDir);

            Vector ref = setColor (rRay, lights, surfaces, limit, root);

            rgb[0] += ref[0] * m->ideal[0];
            rgb[1] += ref[1] * m->ideal[1];
            rgb[2] += ref[2] * m->ideal[2];
        }
        
    }

    return rgb;
}

// Iterate through each pixel
//
void Camera::renderScene (std::vector<Light *>& lights,
                          std::vector<Surface *>& surfaces,
                          BVHNode *root)
{
    std::cout << "rendering..." << std::endl;
    int pixnum = pheight * pwidth;
    pixnum /= 10;
    int n = 0;

    // only one light for now
    Light* light = lights[0];
    Vector rgb(0., 0., 0.);
    
    // for every pixel
    for (int j = 0; j < pheight; ++j) {
        for (int i = 0; i < pwidth; ++i) {
            n++;
            if ((n % pixnum) == 0)
                std::cout << 10 * n / pixnum << "%" << std::endl;

            // color calculations
            Ray ray = generateRay(i, j);
            rgb = setColor (ray, lights, surfaces, 0, root);

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
