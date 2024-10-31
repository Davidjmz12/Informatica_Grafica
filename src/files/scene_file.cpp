#include "files/scene_file.hpp"

#include "geometry/area_light/box_light.hpp"

std::string parse_string(std::string line)
{
    std::regex re0("#.*#"), re1("#.*$"), re2("^\\s+"), re3("\\s+$"), re4("\\s+");
    line = std::regex_replace(line, re0, "");
    line = std::regex_replace(line, re1, "");
    line = std::regex_replace(line, re2, "");
    line = std::regex_replace(line, re3, ""); // Remove comments
    line = std::regex_replace(line, re4, " "); // Remove comments
    return line;
}

std::string SceneFile::read_line() const
{
    std::string line;
    std::getline(this->_file, line);
    line = parse_string(line);
    while(line == "")
    {
        std::getline(this->_file, line);
        line = parse_string(line);
    }
    return line;
}

std::vector<std::string> split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

std::array<int,2> SceneFile::read_resolution() const
{
    std::string line = this->read_line();
    std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 2)
        throw std::invalid_argument("The resolution must have 2 parameters");
    return {std::stoi(tokens[0]), std::stoi(tokens[1])};
}

Point SceneFile::read_point() const
{
    std::string line = this->read_line();
    std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 3)
        throw std::invalid_argument("The point must have 3 parameters");
    return Point(std::stod(tokens[0]), std::stod(tokens[1]), std::stod(tokens[2]));
}

Vector SceneFile::read_vector() const
{
    std::string line = this->read_line();
    std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 3)
        throw std::invalid_argument("The vector must have 3 parameters");
    return Vector(std::stod(tokens[0]), std::stod(tokens[1]), std::stod(tokens[2]));
}

Camera SceneFile::read_camera() const
{
    std::string line = this->read_line();
    if(line != "Camera")
        throw std::invalid_argument("The file must start with the camera section");

    Point center = this->read_point();
    Vector d1 = this->read_vector();
    Vector d2 = this->read_vector();
    Vector d3 = this->read_vector();
    std::array<int,2> res = this->read_resolution();

    return Camera(Base(center, d1, d2, d3), res);
    
}

int SceneFile::read_header(std::string expected) const
{
    std::string line = this->read_line();
    std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 2)
        throw std::invalid_argument("The header must have 2 parameters");
    if (tokens[0] != expected)
        throw std::invalid_argument("The header must start with " + expected);
    return std::stoi(tokens[1]);
}

SpectralColor SceneFile::read_color() const
{
    std::string line = this->read_line();
    std::vector<std::string> tokens = split(line, ' ');
    if (tokens[0] == "RGB")
        return  SpectralColor(SC3{std::stod(tokens[1]), std::stod(tokens[2]), std::stod(tokens[3])});
    else if (tokens[0] == "SC1")
        return SpectralColor(std::stod(tokens[1]));
    else if (tokens[0] == "SC8")
        return SpectralColor(
            SC8{   
                std::stod(tokens[1]), std::stod(tokens[2]), std::stod(tokens[3]), std::stod(tokens[4]), 
                std::stod(tokens[5]), std::stod(tokens[6]), std::stod(tokens[7]), std::stod(tokens[8])
            }
            );
    else if (tokens[0] == "SC16")
        return SpectralColor(
            SC16{   
                std::stod(tokens[1]), std::stod(tokens[2]), std::stod(tokens[3]), std::stod(tokens[4]), 
                std::stod(tokens[5]), std::stod(tokens[6]), std::stod(tokens[7]), std::stod(tokens[8]),
                std::stod(tokens[9]), std::stod(tokens[10]), std::stod(tokens[11]), std::stod(tokens[12]),
                std::stod(tokens[13]), std::stod(tokens[14]), std::stod(tokens[15]), std::stod(tokens[16])
            }
        );
    else if (tokens[0] == "SC32")
        return SpectralColor(
            SC32{
                std::stod(tokens[1]), std::stod(tokens[2]), std::stod(tokens[3]), std::stod(tokens[4]), 
                std::stod(tokens[5]), std::stod(tokens[6]), std::stod(tokens[7]), std::stod(tokens[8]),
                std::stod(tokens[9]), std::stod(tokens[10]), std::stod(tokens[11]), std::stod(tokens[12]),
                std::stod(tokens[13]), std::stod(tokens[14]), std::stod(tokens[15]), std::stod(tokens[16]),
                std::stod(tokens[17]), std::stod(tokens[18]), std::stod(tokens[19]), std::stod(tokens[20]),
                std::stod(tokens[21]), std::stod(tokens[22]), std::stod(tokens[23]), std::stod(tokens[24]),
                std::stod(tokens[25]), std::stod(tokens[26]), std::stod(tokens[27]), std::stod(tokens[28]),
                std::stod(tokens[29]), std::stod(tokens[30]), std::stod(tokens[31]), std::stod(tokens[32])
            }
        );
    else
        throw std::invalid_argument("The color type must be RGB or Spectrum");
}

BRDF* SceneFile::read_brdf(SpectralColor c) const
{
    std::string line = this->read_line();
    if (line == "diffuse")
        return new DiffuseBRDF(c);
    else
        throw std::invalid_argument("The BRDF type must be Diffuse");
}

PropertyHash SceneFile::read_properties() const
{
    int n_properties = this->read_header("Properties");
    PropertyHash ch;
    for (int i = 0; i < n_properties; i++)
    {
        std::string name,line;
        name = this->read_line();
        SpectralColor c = this->read_color();
        BRDF* b = this->read_brdf(c);
        ch[name] = Property(c, b);
    }
    return ch;
}

Property SceneFile::read_property(std::string key, PropertyHash ch) const
{
    if (ch.find(key) == ch.end())
        throw std::invalid_argument("The property " + key + " does not exist");
    return ch[key];
}


Geometry* SceneFile::read_plane(PropertyHash ch) const
{
    Vector normal = this->read_vector();

    std::string line = this->read_line();
    double d = std::stod(line);

    Property color = this->read_property(this->read_line(), ch);
    return new Plane(normal, d, color);
}

Geometry* SceneFile::read_sphere(PropertyHash ch) const
{
    Point center = this->read_point();
    double r = std::stod(this->read_line());
    Property color = this->read_property(this->read_line(), ch);
    return new Sphere(center, r, color);
}

Geometry* SceneFile::read_cylinder(PropertyHash ch) const
{
    Point center = this->read_point();
    double r = std::stod(this->read_line());
    Vector h = this->read_vector();
    Property color = this->read_property(this->read_line(), ch);
    return new Cylinder(center, r, h, color);
}

std::array<double,6> SceneFile::read_bounding_box() const
{
    std::string line = this->read_line();
    std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 6)
        throw std::invalid_argument("The bounding box must have 6 parameters");
    return {std::stod(tokens[0]), std::stod(tokens[1]), std::stod(tokens[2]), std::stod(tokens[3]), std::stod(tokens[4]), std::stod(tokens[5])};
}

Geometry* SceneFile::read_mesh(PropertyHash ch) const
{
    std::string file =  this->_ply_dir + "/" +  this->read_line();
    std::array<double,6> bb = this->read_bounding_box();
    Property color = this->read_property(this->read_line(), ch);
    PlyFile ply = PlyFile(file, color);
    ply = ply.change_bounding_box(bb);
    return ply.to_mesh();
}

Geometry* SceneFile::read_box(PropertyHash ch) const
{
    Point center = this->read_point();
    std::array<Vector,3> axis = {this->read_vector(), this->read_vector(), this->read_vector()};
    Property color = this->read_property(this->read_line(), ch);
    return new Box(center, axis, color);
}

Geometry* SceneFile::read_face(PropertyHash ch) const
{
    Vector normal = this->read_vector();
    Vector u = this->read_vector();
    Vector v = this->read_vector();
    Point point = this->read_point();
    Property color = this->read_property(this->read_line(), ch);
    return new Face(normal, u, v, point, color);
}

Geometry* SceneFile::read_cone(PropertyHash ch) const
{
    return nullptr;
}

Geometry* SceneFile::read_disk(PropertyHash ch) const
{
    Point center = this->read_point();
    Vector normal = this->read_vector();
    double r = std::stod(this->read_line());
    Property color = this->read_property(this->read_line(), ch);
    return new Disk(center, normal, r, color);
}

Geometry* SceneFile::read_ellipsoid(PropertyHash ch) const
{
    double a = std::stod(this->read_line());
    double b = std::stod(this->read_line());
    double c = std::stod(this->read_line());
    Point center = this->read_point();
    Property color = this->read_property(this->read_line(), ch);
    return new Ellipsoid(a, b, c, center, color);
}

Geometry* SceneFile::read_triangle(PropertyHash ch) const
{
    Point p1 = this->read_point();
    Point p2 = this->read_point();
    Point p3 = this->read_point();
    Property color = this->read_property(this->read_line(), ch);
    return new Triangle(p1, p2, p3, color);
}



std::vector<Geometry*> SceneFile::read_geometries(PropertyHash ch) const
{
    int n_geometries = this->read_header("Geometries");
    std::vector<Geometry*> g;
    for (int i = 0; i < n_geometries; i++)
    {
        std::string line = this->read_line();
        if (line == "plane")
            g.push_back(this->read_plane(ch));
        else if(line == "sphere")
            g.push_back(this->read_sphere(ch));
        else if(line == "cylinder")
            g.push_back(this->read_cylinder(ch));
        else if(line == "mesh")
            g.push_back(this->read_mesh(ch));
        else if(line == "box")
            g.push_back(this->read_box(ch));
        else if(line == "face")
            g.push_back(this->read_face(ch));
        else if(line == "cone")
            g.push_back(this->read_cone(ch));
        else if(line == "disk")
            g.push_back(this->read_disk(ch));
        else if(line == "ellipsoid")
            g.push_back(this->read_ellipsoid(ch));
        else if(line == "triangle")
            g.push_back(this->read_triangle(ch));
        else
            throw std::invalid_argument("The geometry type must be Plane, Sphere, Cone or Ply");
    }
    return g;   
}

SceneFile::SceneFile(std::string file, std::string ply_dir):
    _ply_dir(ply_dir)
{
    this->_file.open(file);
    if (!this->_file.is_open())
        throw std::invalid_argument("The file " + file + " does not exist");
}

std::vector<Light> SceneFile::read_lights() const
{
    int n_lights = this->read_header("Lights");
    std::vector<Light> l;
    for (int i = 0; i < n_lights; i++)
    {
        this->read_line(); // Discard the light name
        Point p = this->read_point();
        SpectralColor c = this->read_color();
        l.push_back(Light(p, c));
    }
    return l;
}

ToneMapping* SceneFile::read_gamma_tm(double max) const
{
    std::string line = this->read_line();
    std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 2)
        throw std::invalid_argument("The gamma tone mapping must have 1 parameter");
    double gamma = std::stod(tokens[0]);
    double L;
    if(tokens[1] == "max")
        L = max;
    else
        L = std::stod(tokens[1]);
    
    return new Gamma(gamma,L);
}

ToneMapping* SceneFile::read_tone_mapping(double max) const
{
    std::string line = this->read_line();
    if(line != "ToneMapping")
        throw std::invalid_argument("The file must have a tone mapping section");
    line = this->read_line();
    if (line == "gamma")
        return this->read_gamma_tm(max);
    else
        throw std::invalid_argument("Tone mapping not recognized");
}


void SceneFile::read_scene(std::string file_save) const
{
    Camera c = this->read_camera();
    PropertyHash ch = this->read_properties();
    std::vector<Geometry*> g = this->read_geometries(ch);
    std::vector<Light> l = this->read_lights();

    std::vector<AreaLight*> al;
    al.push_back(new BoxLight(Box(Point(-0.5,1,-0.5),{Vector(0.3,0,0),Vector(0,0,0.3),Vector(0,-0.2,0)},Property(SpectralColor(1))),SpectralColor(10)));
    
    Scene s = Scene(g, l, al, c);
    PpmFile ppm = PpmFile(s);

    ToneMapping* t = this->read_tone_mapping(ppm.get_max_range());
    ppm = ppm.apply_tone_mapping(t, 255);
    ppm.save(file_save);
}