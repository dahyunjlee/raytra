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

#include "camera.h"
#include "surface.h"
//#include "light.h"
#include "material.h"


class Parser {
public:
    void parse(
            const char *file,
            std::vector<Surface *>& surfaces,
            std::vector<Light *>& lights,
            std::vector<Material *>& materials,
            Camera& cam);

};

#endif
