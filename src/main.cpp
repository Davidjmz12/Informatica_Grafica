#include <iostream>
#include <cstring>

#include "global_config/global_config.hpp"
#include "threading/thread_pool.hpp"
#include "metrics/metrics.hpp"
#include "files/scene_file.hpp"

HashMap get_default_conf() {
    HashMap conf;
    conf["threads"] = int(1);
    conf["rays"] = int(1);
    #ifdef METRICS
    conf["metrics"] = Metrics();
    #endif
    conf["task-size"] = int(32);
    conf["bounces"] = int(5);
    conf["max-depth"] = int(7);
    conf["file-in"] = std::string("in/test.txt");
    conf["file-out"] = std::string("out/example.ppm");
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

        if(std::strcmp(argv[i], "--file-in") == 0)
        {
            std::string file_in = std::string(argv[i + 1]);
            conf["file-in"] = file_in;
            i++;
        }

        if(std::strcmp(argv[i], "--file-out") == 0)
        {
            std::string file_out = std::string(argv[i + 1]);
            conf["file-out"] = file_out;
            i++;
        }

    }

    GlobalConf::get_instance(conf);
}

void parse_end() {
    
    #ifdef METRICS
    Metrics m = GlobalConf::get_instance()->get_metrics();
    m.print_metrics();
    #endif

    delete GlobalConf::get_instance();
}

int main(const int argc, char* argv[])
{
    try {
        parse_init(argc, argv);

        auto sf = SceneFile(std::string(ASSETS_DIR) + "/" + GlobalConf::get_instance()->get_file_in()  , std::string(ASSETS_DIR));

        sf.read_scene(std::string(ASSETS_DIR) + "/" + GlobalConf::get_instance()->get_file_out());

        parse_end();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}