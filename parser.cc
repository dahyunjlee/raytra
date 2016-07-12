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

    Material *lastMaterialLoaded = 0;
    
    for (int line=1; inFile.good(); line++) {
        inFile.getline(buffer, 1024);
        buffer[inFile.gcount()]=0;

        Surface *thisSurface = 0;

        cmd = "";

        istringstream iss(buffer);

        iss >> cmd;

        if (cmd[0]=='#' or cmd[0]=='/' or cmd.empty()) {
            //ignore comments or blank lines
            continue;
        }
        else if (cmd=="s") {
            // got a sphere
            cout<<"Got a Sphere"<<endl;

            double x, y, z, r;
            iss >> x >> y >> z >> r;
            thisSurface = new Sphere(Point(x, y, z), r);

        }
        else if (cmd=="t") {
            // got a triangle
            cout<<"Got a Triangle"<<endl;

            double x1, y1, z1, x2, y2, z2, x3, y3, z3;
            iss >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
            Point p1(x1, y1, z1);
            Point p2(x2, y2, z2);
            Point p3(x3, y3, z3);
            thisSurface = new Triangle(p1, p2, p3);

        }
        else if (cmd=="c") {
            // got a camera
            cout<<"Got a Camera"<<endl;
            num_cams++;

            double ex, ey, ez, vx, vy, vz, d;
            double iw, ih, pw, ph;
            iss >> ex >> ey >> ez >> vx >> vy >> vz >> d;
            iss >> iw >> ih >> pw >> ph;

            cam.init(Point(ex, ey, ez), Vector(vx, vy, vz), d, iw, ih, pw, ph);
        }
        else if (cmd=="m") {
            // got a material
            double dr, dg, db, sr, sg, sb, pe, ir, ig, ib;
            iss >> dr >> dg >> db >> sr >> sg >> sb >> pe >> ir >> ig >> ib;
            lastMaterialLoaded = new Material (dr, dg, db, sr, sg, sb, pe, ir, ig, ib);
            materials.push_back (lastMaterialLoaded);
        }

        else if (cmd=="l") {
            // got a light

            iss >> cmd;
            if (cmd=="p") {
                //point light
                double posx, posy, posz, r, g, b;
                iss >> posx >> posy >> posz >> r >> g >> b;
                lights.push_back (new PLight (Point(posx, posy, posz), r, g, b));
            }
        }
     
        if (thisSurface)
            surfaces.push_back(thisSurface);
        if (lastMaterialLoaded && thisSurface)
            thisSurface->setMaterial(lastMaterialLoaded);
    }

    if (num_cams != 1) {
        cerr << "There must be only one camera." << endl;
        exit (-1);
    }
}


