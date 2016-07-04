// 
// main.cc
//

#include <iostream>
#include <stdlib.h>
#include <vector>

#include "parser.h"
#include "camera.h"
#include "surface.h"

using namespace std;

int main (int argc, const char** argv)
{
    clock_t start = clock();

    if (argc != 3) {
        std::cout << "usage: raytra scenefile outputimage" << std::endl;
        exit (-1);
    }

    vector<Surface *>surfaces;
    Camera cam;
    Parser parser;
    parser.parse (argv[1], surfaces, cam);

    cam.renderScene(surfaces);
    cam.writeImage(argv[2]);

    double duration = (clock()-start) / (double) CLOCKS_PER_SEC;
    cout<< duration << "s" << endl;
    return 0;
}
