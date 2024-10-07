#include <iostream>
#include "scene.hpp"
#include "geometry/sphere.hpp"
#include "geometry/disk.hpp"
#include "geometry/plane.hpp"
#include "geometry/triangle.hpp"
#include "ppm_file.hpp"
#include "geometry/cylinder.hpp"

int main()
{
    Base b = Base(Point(),Vector(0,1,0),Vector(0,0,1),Vector(1,0,0));
    Camera c = Camera(b, 800, 600, 3600);
    Geometry* el = new Sphere(Point(c.c_cam(new Point(300,400,3600))),100);
    Geometry* t = new Triangle( Point(c.c_cam(new Point(300,400,3600))),
                                Point(c.c_cam(new Point(300,600,3600))),
                                Point(c.c_cam(new Point(400,400,3600))));
    Geometry* ccc = new Cylinder(Point(c.c_cam(new Point(300,400,3600))),100,Vector(0,200,0));
    //Geometry* e2 = new Sphere(Point(4000,600,500),100);
    //Geometry* el = new Disk(Point(4000,400,300),Vector(1,0,0),200);
    std::vector<Geometry*> ve = {ccc};
    Scene s = Scene(ve, c);

    ColorMap cm = s.paint_scene();

    PpmFile ppm = PpmFile(cm, 255, 255, {800,600}, "P3");
    ppm.save("../../assets/out/scene.ppm");
}