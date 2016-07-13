// 
// parser.h
// parses scene files into geometry, camera, lights, etc
//

#ifndef PARSER_H_
#define PARSER_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "camera.h"

using namespace std;

class Parser {
public:
    void parse(
            const char *file,
            std::vector<Surface *>& surfaces,
            std::vector<Light *>& lights,
            std::vector<Material *>& materials,
            Camera& cam);

    void read_wavefront_file (const char *file, std::vector<int>& tris,
                              std::vector<float>& verts);

};

#endif
