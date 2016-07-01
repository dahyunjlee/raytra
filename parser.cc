//
// parser.cc
//

#include "parser.h"

using namespace std;

void Parser::parse(
        const char *file,
        std::vector<Surface *>& surfaces,
        std::vector<Light *>& lights,
        std::vector<Material *>& materials,
        Camera& cam)
{
    ifstream inFile(file);
    char buffer[1025];
    string cmd;

    int num_cams = 0;

    if (!inFile.is_open()) {
        cerr << "Failed to open scene file." << endl;
        exit (-1);
    }

    //Material *lastMaterialLoaded = 0;
    
    for (int line=1; inFile.good(); line++) {
        inFile.getline(buffer, 1024);
        buffer[inFile.gcount()]=0;

        cmd = "";

        istringstream iss(buffer);

        iss >> cmd;

        if (cmd[0]=='#' or cmd[0]=='/' or cmd.empty()) {
            //ignore comments or blank lines
            continue;
        }
        else if (cmd=="s") {
            // got a sphere

            double x, y, z, r;
            iss >> x >> y >> z >> r;

        }
        else if (cmd=="c") {
            // got a camera
            double ex, ey, ez, vx, vy, vz, d;
            int iw, ih, pw, ph;
            iss >> ex >> ey >> ez >> vx >> vy >> vz >> d;
            iss >> iw >> ih >> pw >> ph;

            num_cams++;
        }
    }
}


