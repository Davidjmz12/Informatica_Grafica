#include <iostream>
#include "scene.hpp"
#include "geometry/all_geometry.hpp"
#include "ppm_file.hpp"
#include "ply_file.hpp"

int main()
{
    //PlyFile ply = PlyFile("../../assets/in/cow.ply");
    //PlyFile ply2 = ply.change_bounding_box({-0.5,0.5,-0.5,0.5,2,3});
    //Geometry* t = new TriangleMesh(ply2.get_triangles());

    Base b = Base(Point(),Vector(800,0,0),Vector(0,600,0),Vector(0,0,10000));
    Camera c = Camera(b);
    Geometry* e1 = new Plane(Point(0,-1,0),Vector(0,1,0));
    Geometry* e2 = new Plane(Point(0,1,0),Vector(0,-1,0));
    Geometry* e3 = new Plane(Point(1,0,0),Vector(-1,0,0));
    Geometry* e4 = new Plane(Point(-1,0,0),Vector(1,0,0));
    Geometry* e5 = new Plane(Point(0,0,4),Vector(0,0,-1));

    //Geometry* ss = new Box(Point(0.5,0.5,2),{0.5,0.5,0.5},{Vector(1,2,0).normalize(),Vector(0,1,3).normalize(),Vector(5,0,1).normalize()});
    Geometry* face = new Face(Vector(0,0,1),Vector(0.5,0,0),Vector(0,0.25,0),Point(0,0,2));
    std::vector<Geometry*> ve = {face};
    Scene s = Scene(ve, c);

    ColorMap cm = s.paint_scene();

    PpmFile ppm = PpmFile(cm, 255, 255, {1600,1200}, "P3");
    ppm.save("../../assets/out/scene.ppm");
}