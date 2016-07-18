// // bvh.cc
//

#include "bvh.h"

bool sortx(Surface *a, Surface *b) {
    return (a->bbox.min.x < b->bbox.min.x);
}
bool sorty(Surface *a, Surface *b) {
    return (a->bbox.min.y < b->bbox.min.y);
}
bool sortz(Surface *a, Surface *b) {
    return (a->bbox.min.z < b->bbox.min.z);
}

BVHNode::BVHNode(vector <Surface*> &objects, int l, int r, int axis) {
    
    // leaf level-- surfaces are on left child 
    if (l==r) {
        left = objects[l];
        left->bbox.id = l;
        right = NULL;
    }
    else if (l < r) {
        surround (objects, l, r);
        if (r == l + 1) {
            left = objects[l];
            left->bbox.id = l;
            right = objects[r];
            right->bbox.id = r;
        }
        else {
            int mid = l + (r-l)/2;
            switch (axis) {
                case 0:
                    nth_element (objects.begin() + l, objects.begin() + mid,
                                 objects.begin() + r + 1, sortx);
                    break;
                case 1:
                    nth_element (objects.begin() + l, objects.begin() + mid,
                                 objects.begin() + r + 1, sorty);
                    break;
                case 2:
                    nth_element (objects.begin() + l, objects.begin() + mid,
                                 objects.begin() + r + 1, sortz);
                    break;
            }
            
            left = new BVHNode (objects, l, mid, (axis+1)%3);
            right = new BVHNode (objects, mid+1, r, (axis+1)%3);
        }
    }
}

void BVHNode::surround(const vector<Surface *>objects, int l, int r) {
    
    double minx, maxx, miny, maxy, minz, maxz;

    minx = miny = minz = INFINITY;
    maxx = maxy = maxz = -INFINITY;

    for (int i = l; i <= r; ++i) {
        minx = fmin (minx, objects[i]->bbox.min.x);
        miny = fmin (miny, objects[i]->bbox.min.y);
        minz = fmin (minz, objects[i]->bbox.min.z);

        maxx = fmax (maxx, objects[i]->bbox.max.x);
        maxy = fmax (maxy, objects[i]->bbox.max.y);
        maxz = fmax (maxz, objects[i]->bbox.max.z);
    }

    bbox = BBox (Point (minx, miny, minz), Point (maxx, maxy, maxz));
    bbox.expand(e);
}

bool BVHNode::intersect(const Ray &ray, Intersection &it) {

    // 
    if (right==NULL) {
        if (left->intersect(ray, it) && it.t > e)
            return true;
    }
    else if (bbox.intersect(ray, it)) {
        cout<<"bboxhit";
        Intersection l, r;
        bool lhit = left->intersect(ray, l) && l.t > e;
        bool rhit = right->intersect(ray, r) && r.t > e;
        if (!lhit && !rhit)
            return false;
        else {
            cout<<"hit"<<endl;
            // find closest intersection
            if (lhit && rhit) {
                if (l.t < r.t)
                    it = l;
                else
                    it = r;
            }
            else if (lhit)
                it = l;
            else
                it = r;
            return true;
        }
    }
    return false;
}

bool BVHNode::shadowTest(const Ray &ray, Intersection &it) {

    if (right == NULL) {
        if (left->intersect(ray, it) && it.t > e)
            return true;
    }
    else if (bbox.intersect(ray, it)) {
        bool hit = left->intersect(ray, it) && it.t > e;
        if (hit)
            return true;

        hit = right->intersect(ray, it) && it.t > e;
        if (hit)
            return true;
    }
    return false;
}
