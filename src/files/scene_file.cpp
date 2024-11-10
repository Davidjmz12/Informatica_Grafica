#include "files/scene_file.hpp"

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

    do {
        std::getline(this->_file, line);
        line = parse_string(line);
    } while(line == "");

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

BRDF* SceneFile::read_brdf() const
{
    std::string line = this->read_line();
    if (line == "diffuse")
        return new DiffuseBRDF(this->read_color());
    else if (line == "specular")
        return new SpecularBRDF(this->read_color());
    else if (line == "absorption")
        return new AbsorptionBRDF();
    else if (line == "refractive")
    {
        SpectralColor c = this->read_color();
        double refractive_index = std::stod(this->read_line());
        return new RefractiveBRDF(c, refractive_index);
    }
    else if (line == "roulette")
    {
        int n_brdfs = std::stoi(this->read_line());
        std::vector<BRDF*> brdfs;
        std::vector<double> weights;
        for (int i = 0; i < n_brdfs; i++)
        {
            brdfs.push_back(this->read_brdf());
            weights.push_back(std::stod(this->read_line()));
        }
        return new RouletteBRDF(brdfs, weights);
    }
        
    else
        throw std::invalid_argument("The BRDF type must be Diffuse");
}

void SceneFile::read_properties()
{
    int n_properties = this->read_header("Properties");
    for (int i = 0; i < n_properties; i++)
    {
        std::string name,line;
        name = this->read_line();
        BRDF* b = this->read_brdf();
        this->_ch[name] = Property(b);
    }
}

Property SceneFile::read_property(std::string key) const
{
    if (this->_ch.find(key) == this->_ch.end())
        throw std::invalid_argument("The property " + key + " does not exist");
    PropertyHash ph = this->_ch;
    return ph[key];
}


Geometry* SceneFile::read_plane(Property p) const
{
    Vector normal = this->read_vector();

    std::string line = this->read_line();
    double d = std::stod(line);

    return new Plane(normal, d, p);
}

Geometry* SceneFile::read_sphere(Property p) const
{
    Point center = this->read_point();
    double r = std::stod(this->read_line());
    return new Sphere(center, r, p);
}

Geometry* SceneFile::read_cylinder(Property p) const
{
    Point center = this->read_point();
    double r = std::stod(this->read_line());
    Vector h = this->read_vector();
    return new Cylinder(center, r, h, p);
}

std::array<double,6> SceneFile::read_bounding_box() const
{
    std::string line = this->read_line();
    std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 6)
        throw std::invalid_argument("The bounding box must have 6 parameters");
    return {std::stod(tokens[0]), std::stod(tokens[1]), std::stod(tokens[2]), std::stod(tokens[3]), std::stod(tokens[4]), std::stod(tokens[5])};
}

Geometry* SceneFile::read_mesh(Property p) const
{
    std::string file =  this->_ply_dir + "/" +  this->read_line();
    std::array<double,6> bb = this->read_bounding_box();
    PlyFile ply = PlyFile(file, p);
    ply = ply.change_bounding_box(bb);
    return ply.to_mesh();
}

Geometry* SceneFile::read_box(Property p) const
{
    Point center = this->read_point();
    std::array<Vector,3> axis = {this->read_vector(), this->read_vector(), this->read_vector()};
    return new Box(center, axis, p);
}

Geometry* SceneFile::read_face(Property p) const
{
    Vector normal = this->read_vector();
    Vector u = this->read_vector();
    Vector v = this->read_vector();
    Point point = this->read_point();
    return new Face(normal, u, v, point, p);
}

Geometry* SceneFile::read_cone(Property p) const
{
    Point vertex = this->read_point();
    Vector axe = this->read_vector();
    double h = std::stod(this->read_line());
    double r = std::stod(this->read_line());
    return new Cone(vertex, axe, h, r, p);
}

Geometry* SceneFile::read_disk(Property p) const
{
    Point center = this->read_point();
    Vector normal = this->read_vector();
    double r = std::stod(this->read_line());
    return new Disk(center, normal, r, p);
}

Geometry* SceneFile::read_ellipsoid(Property p) const
{
    double a = std::stod(this->read_line());
    double b = std::stod(this->read_line());
    double c = std::stod(this->read_line());
    Point center = this->read_point();
    return new Ellipsoid(a, b, c, center, p);
}

Geometry* SceneFile::read_triangle(Property p) const
{
    Point p1 = this->read_point();
    Point p2 = this->read_point();
    Point p3 = this->read_point();
    return new Triangle(p1, p2, p3, p);
}

Geometry* SceneFile::read_geometry() const
{
    // Read the type of geometry
    std::string line = this->read_line();

    // Read the property
    Property p = this->read_property(this->read_line());

    // Create the appropiate object
    if (line == "plane")
        return this->read_plane(p);
    else if(line == "sphere")
        return this->read_sphere(p);
    else if(line == "cylinder")
        return this->read_cylinder(p);
    else if(line == "mesh")
        return this->read_mesh(p);
    else if(line == "box")
        return this->read_box(p);
    else if(line == "face")
        return this->read_face(p);
    else if(line == "cone")
        return this->read_cone(p);
    else if(line == "disk")
        return this->read_disk(p);
    else if(line == "ellipsoid")
        return this->read_ellipsoid(p);
    else if(line == "triangle")
        return this->read_triangle(p);
    else
        throw std::invalid_argument("The geometry type is unknown");
}

std::vector<Geometry*> SceneFile::read_geometries() const
{
    // Read header and number of geometries
    int n_geometries = this->read_header("Geometries");
    std::vector<Geometry*> g;

    // Read all geometries
    for (int i = 0; i < n_geometries; i++)
        g.push_back(this->read_geometry());

    return g;   
}

SceneFile::SceneFile(std::string file, std::string ply_dir):
    _ply_dir(ply_dir)
{
    this->_file.open(file);
    if (!this->_file.is_open())
        throw std::invalid_argument("The file " + file + " does not exist");
}

void SceneFile::read_lights(std::vector<PunctualLight*>& pl, std::vector<AreaLight*>& al) const
{
    // Read header and number of lights
    int n_lights = this->read_header("Lights");

    // Read all lights
    for (int i = 0; i < n_lights; i++)
    {
        // Read type of light
        std::string name = this->read_line();

        // Create the appropiate type of light
        if (name == "punctual")
            pl.push_back(this->read_punctual_light());
        else if (name == "area")
            al.push_back(this->read_area_light()); 
        else
            throw std::invalid_argument("Unknown light type.");
    }
}

PunctualLight* SceneFile::read_punctual_light() const
{
    SpectralColor power = this->read_color();
    Point center = this->read_point();
    return new PunctualLight(center, power);
}

AreaLight* SceneFile::read_area_light() const
{
    // Read the geometry
    Geometry* g = this->read_geometry();

    // Create the area light
    return new AreaLight(g, g->get_properties().get_color());
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


void SceneFile::read_scene(std::string path, std::string file_save)
{
    Camera c = this->read_camera();
    this->read_properties();
    std::vector<Geometry*> g = this->read_geometries();
    std::vector<PunctualLight*> pl;
    std::vector<AreaLight*> al;
    this->read_lights(pl, al);
    
    Render rend = Render(Scene(g, pl, al, c));

    ColorMap cm = rend.render_scene();
    double max = cm.max();
    PpmFile ppm = PpmFile(cm, max, max, rend.get_resolution(), "P3");
    
    ppm.save(path + "/" + "no_tm_" + file_save);

    ToneMapping* t = this->read_tone_mapping(ppm.get_max_range());
    PpmFile ppm_tm = ppm.apply_tone_mapping(t, 255);
    ppm_tm.save(path + "/" + file_save);
}