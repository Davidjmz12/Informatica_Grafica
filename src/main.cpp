#include <iostream>
#include <cstring>

#include "global_config/global_config.hpp"
#include "threading/thread_pool.hpp"
#include "metrics/metrics.hpp"
#include "files/scene_file.hpp"

HashMap get_default_conf() {
    HashMap conf;
    conf["threads"] = int(10);
    conf["rays"] = int(1);
    conf["is-metrics"] = bool(true);
    conf["metrics"] = Metrics();
    conf["task-size"] = int(256);
    conf["bounces"] = int(3);
    conf["max-depth"] = int(0);
    return conf;
}

void parse_init(const int argc, char* argv[]) {
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

        if(std::strcmp(argv[i], "--bounces") == 0)
        {
            int n_bounces = int(std::stoi(argv[i+1]));
            conf["bounces"] = n_bounces;
            i++;
        }

        if(std::strcmp(argv[i], "--max-depth") == 0)
        {
            int max_depth = int(std::stoi(argv[i + 1]));
            conf["max-depth"] = max_depth;
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

int main(const int argc, char* argv[])
{
    try {
        parse_init(argc, argv);

        auto sf = SceneFile(std::string(ASSETS_DIR) + "/in/scene.txt", std::string(ASSETS_DIR));

        sf.read_scene(std::string(ASSETS_DIR) + "/out","scene.ppm");

        parse_end();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}