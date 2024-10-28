#include <iostream>
#include <cstring>

#include "global_config/global_config.hpp"
#include "threading/thread_pool.hpp"
#include "metrics/metrics.hpp"

#include "scene.hpp"
#include "geometry/all_geometry.hpp"
#include "files/ppm_file.hpp"
#include "files/ply_file.hpp"
#include "color/tone_mapping/all_tone_mapping.hpp"


HashMap get_default_conf() {
    HashMap conf;
    conf["threads"] = int(16);
    conf["rays"] = int(10);
    conf["is-metrics"] = bool(true);
    conf["metrics"] = Metrics();
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

        if(std::strcmp(argv[i], "-metrics") == 0)
        {
            conf["is-metrics"] = bool(true);
            conf["metrics"] = Metrics();
        }
    }

    GlobalConf::get_instance(conf);
}

void parse_end() {
    GlobalConf* gc = GlobalConf::get_instance(); 

    if(gc->has_metrics())
    {
        Metrics m = gc->get_metrics();
        m.print_metrics();
    }

    delete GlobalConf::get_instance();
}

int main(int argc, char* argv[]) 
{
    // Define the spectral color contributions of Salmon

    parse_init(argc, argv);

    Base b = Base(Point(0,0,-3.5),Vector(-1,0,0),Vector(0,1,0),Vector(0,0,3));
    Camera c = Camera(b,{256,256});

    Property red = Property(SpectralColor(SC3{1,0,0}));
    Property green = Property(SpectralColor(SC3{0,1,0}));
    Property blue = Property(SpectralColor(SC3{0,0,1}));
    Property yellow = Property(SpectralColor(SC3{1,1,0}));
    Property cyan = Property(SpectralColor(SC3{0,1,1}));
    Property magenta = Property(SpectralColor(SC3{1,0,1}));
    Property white = Property(SpectralColor(1));

    Geometry* p1 = new Plane(Vector(1,0,0),1,red);
    Geometry* p2 = new Plane(Vector(-1,0,0),1,green);
    Geometry* p3 = new Plane(Vector(0,1,0),1,blue);
    Geometry* p4 = new Plane(Vector(0,-1,0),1,yellow);
    Geometry* p5 = new Plane(Vector(0,0,-1),1,cyan);
    Geometry* sp1 = new Sphere(Point(-0.5,-0.7,0.25),0.3,magenta);
    Geometry* sp2 = new Sphere(Point(0.5,-0.7,-0.25),0.3,white);
    Geometry* cone = new Cone(Point(0,0,0),Vector(0,-1,0),0.5,0.5,white);
    

    Light l1 = Light(Point(0,0.5,0),SpectralColor(0.5));
    Light l2 = Light(Point(0.5,0,0),SpectralColor(0.5));
    PlyFile ply = PlyFile(std::string(ASSETS_DIR) + "/in/cow.ply",magenta);
    ply = ply.change_bounding_box({-0.8,-0.2,-1,-0.4,-0.05,0.55});
    Geometry* sp3 = ply.to_mesh();

    Scene s = Scene({p1,p2,p3,p4,p5,sp3,sp2}, {l1}, c);

    PpmFile ppm = PpmFile(s);

    ppm = ppm.apply_tone_mapping(new Gamma(2,ppm.get_max_range()), 255);

    ppm.save(std::string(ASSETS_DIR) + "/out/scene.ppm");

    parse_end();
    return 0;
}