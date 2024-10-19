#include <iostream>
#include <cstring>

#include "global_config/global_config.hpp"
#include "threading/thread_pool.hpp"

#include "scene.hpp"
#include "geometry/all_geometry.hpp"
#include "ppm_file.hpp"
#include "ply_file.hpp"


HashMap get_default_conf() {
    HashMap conf;
    conf["threads"] = int(1);
    conf["rays"] = int(10);
    return conf;
}

void parse_init(int argc, char* argv[]) {
    HashMap conf = get_default_conf();
    for (int i = 1; i < argc; i++) {
        if(std::strcmp(argv[i], "--threads") == 0)
        {
            int threads = int(std::stoi(argv[i+1]));
            conf["threads"] = threads;
            i++;
        }

        if(std::strcmp(argv[i], "--rays") == 0)
        {
            int rays = int(std::stoi(argv[i+1]));
            conf["rays"] = rays;
            i++;
        }
    }

    GlobalConf::get_instance(conf);
}

int main(int argc, char* argv[]) 
{
    parse_init(argc, argv);

    Base b = Base(Point(0,0,-3.5),Vector(-1,0,0),Vector(0,1,0),Vector(0,0,3));
    Camera c = Camera(b,{256,256});

    Property red = Property(Color({255,0,0},{255,255,255},ColorEncoding::RGB));
    Property green = Property(Color({0,255,0},{255,255,255},ColorEncoding::RGB));
    Property blue = Property(Color({0,0,255},{255,255,255},ColorEncoding::RGB));
    Property yellow = Property(Color({255,255,0},{255,255,255},ColorEncoding::RGB));
    Property cyan = Property(Color({0,255,255},{255,255,255},ColorEncoding::RGB));
    Property magenta = Property(Color({255,0,255},{255,255,255},ColorEncoding::RGB));
    Property white = Property(Color({255,255,255},{255,255,255},ColorEncoding::RGB));

    Geometry* p1 = new Plane(Vector(1,0,0),1,cyan);
    Geometry* p2 = new Plane(Vector(-1,0,0),1,yellow);
    Geometry* p3 = new Plane(Vector(0,1,0),1,blue);
    Geometry* p4 = new Plane(Vector(0,-1,0),1,green);
    Geometry* p5 = new Plane(Vector(0,0,-1),1,red);
    Geometry* sp1 = new Sphere(Point(-0.5,-0.7,0.25),0.3,magenta);
    Geometry* sp2 = new Sphere(Point(0.5,-0.7,-0.25),0.3,white);
    
    Scene s = Scene({p1,p2,p3,p4,p5,sp1,sp2}, c);

    PpmFile ppm = PpmFile(s);

    ppm.save("assets/out/scene.ppm");

    return 0;
}