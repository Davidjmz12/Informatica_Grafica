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
    Base b = Base(Point(),Vector(800,0,0),Vector(0,600,0),Vector(0,0,10000));
    Camera c = Camera(b);
    //Geometry* e1 = new Sphere(Point(new Point(0,0,3600)),1000);
    //Geometry* e2 = new Sphere(Point(4000,600,500),100);
    //Geometry* e1 = new Disk(Point(0,0,10),Vector(0,0,1),1);
    Geometry* e1 = new Plane(Point(0,-1,0),Vector(0,1,0));
    Geometry* e2 = new Plane(Point(0,1,0),Vector(0,-1,0));
    Geometry* e3 = new Plane(Point(1,0,0),Vector(-1,0,0));
    Geometry* e4 = new Plane(Point(-1,0,0),Vector(1,0,0));
    Geometry* e5 = new Plane(Point(0,0,3),Vector(0,0,-1));
    //Geometry* ss = new Sphere(Point(0,0,2),0.1);
    Geometry* ss = new Cylinder(Point(0,0,1.5),0.2,Vector(1/4.0,1/3.0,0.3));
    std::vector<Geometry*> ve = {e1,e2,e3,e4,e5,ss};
    Scene s = Scene(ve, c);

    ColorMap cm = s.paint_scene();

    PpmFile ppm = PpmFile(cm, 255, 255, {1600,1200}, "P3");
    ppm.save("../../assets/out/scene.ppm");
}