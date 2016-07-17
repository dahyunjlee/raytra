// 
// bvh.h
//

#ifndef BVH_H_
#define BVH_H_

#include <vector>
#include <algorithm>
#include "surface.h"

const double e = 0.0001;

using namespace std;

class BVHNode : public Surface {

public:

    BVHNode() :left(NULL), right(NULL) {}
    BVHNode(vector <Surface*> &objects, int l, int r, int axis);

    void surround (const vector<Surface*> objects, int l, int r);

    bool intersect(const Ray &ray, Intersection &it);
    bool shadowTest(const Ray &ray, Intersection &it);

    // bvhnode public data
    //
    Surface *left;
    Surface *right;

};

#endif
