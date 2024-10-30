#include <iostream>
#include <cstring>

#include "global_config/global_config.hpp"
#include "threading/thread_pool.hpp"
#include "metrics/metrics.hpp"

#include "files/scene_file.hpp"

#include "geometry/area_light/box_light.hpp"


HashMap get_default_conf() {
    HashMap conf;
    conf["threads"] = int(12);
    conf["rays"] = int(10);
    conf["is-metrics"] = bool(true);
    conf["metrics"] = Metrics();
    conf["task-size"] = int(100);
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

        if(std::strcmp(argv[i], "--task-size") == 0)
        {
            int task_size = int(std::stoi(argv[i+1]));
            conf["task-size"] = task_size;
            i++;
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
    parse_init(argc, argv);

    BoxLight(Box(Point(),{Vector(1,0,0),Vector(0,1,0),Vector(0,0,1)},Property()), SpectralColor());

    SceneFile sf = SceneFile(std::string(ASSETS_DIR) + "/in/scene.txt", std::string(ASSETS_DIR));

    sf.read_scene(std::string(ASSETS_DIR) + "/out/scene.ppm");

    parse_end();
    return 0;
}