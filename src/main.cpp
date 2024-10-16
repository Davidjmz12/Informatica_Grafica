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

    Base b = Base(Point(0,0,-3.5),Vector(-1,0,0),Vector(0,1,0),Vector(0,0,3));
    Camera c = Camera(b);

    Property properties = Property(Color({255,0,0},{255,255,255},ColorEncoding::RGB));

    Geometry* p1 = new Plane(Vector(1,0,0),1,properties);
    Geometry* p2 = new Plane(Vector(-1,0,0),1,properties);
    Geometry* p3 = new Plane(Vector(0,1,0),1,properties);
    Geometry* p4 = new Plane(Vector(0,-1,0),1,properties);
    Geometry* p5 = new Plane(Vector(0,0,-1),1,properties);

    //Geometry* ss = new Box(Point(0.5,0.5,2),{0.5,0.5,0.5},{Vector(1,2,0).normalize(),Vector(0,1,3).normalize(),Vector(5,0,1).normalize()});
    Scene s = Scene({p1,p2,p3,p4,p5}, c);

    ColorMap cm = s.paint_scene();

    PpmFile ppm = PpmFile(cm, 255, 255, {256,256}, "P3");
    ppm.save("../../assets/out/scene.ppm");
}