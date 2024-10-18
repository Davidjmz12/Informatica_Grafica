#include <iostream>
#include "scene.hpp"
#include "geometry/all_geometry.hpp"
#include "ppm_file.hpp"
#include "ply_file.hpp"

int main()
{

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
    

    //PlyFile ply = PlyFile("../../assets/in/diamond.ply");
    //PlyFile ply2 = ply.change_bounding_box({0.2,-1,-0.55,0.8,-0.4,0.05});
    //Geometry* sp3 = new TriangleMesh(ply2.get_triangles(),white);

    //Geometry* sp3 = new Ellipsoid(0.3,0.1,0.5,Point(0.5,-0.7,-0.25),white);
    //Geometry* sp3 = new Cylinder(Point(0.5,-0.7,-0.25),0.3,Vector(0,1,0),white);
    //Geometry* ss = new Box(Point(0.5,0.5,2),{0.5,0.5,0.5},{Vector(1,2,0).normalize(),Vector(0,1,3).normalize(),Vector(5,0,1).normalize()});
    Scene s = Scene({p1,p2,p3,p4,p5,sp1,sp2}, c);

    PpmFile ppm = PpmFile(s,10);

    ppm.save("../../assets/out/scene.ppm");
}