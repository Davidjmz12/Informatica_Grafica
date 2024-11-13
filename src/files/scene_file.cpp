#include <utility>
#include "color/tone_mapping/all_tone_mapping.hpp"

#include "files/scene_file.hpp"

std::string parse_string(std::string line)
{
    const std::regex re0("#.*#");
    const std::regex re1("#.*$");
    const std::regex re2("^\\s+");
    const std::regex re3("\\s+$");
    const std::regex re4("\\s+");
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
    } while(line.empty());

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
    const std::string line = this->read_line();
    const std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 2)
        throw std::invalid_argument("The resolution must have 2 parameters");
    return {std::stoi(tokens[0]), std::stoi(tokens[1])};
}

Point SceneFile::read_point() const
{
    const std::string line = this->read_line();
    const std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 3)
        throw std::invalid_argument("The point must have 3 parameters");
    return {std::stod(tokens[0]), std::stod(tokens[1]), std::stod(tokens[2])};
}

Vector SceneFile::read_vector() const
{
    const std::string line = this->read_line();
    const std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 3)
        throw std::invalid_argument("The vector must have 3 parameters");
    return {std::stod(tokens[0]), std::stod(tokens[1]), std::stod(tokens[2])};
}

Camera SceneFile::read_camera() const
{
    const std::string line = this->read_line();
    if(line != "Camera")
        throw std::invalid_argument("The file must start with the camera section");

    const Point center = this->read_point();
    const Vector d1 = this->read_vector();
    const Vector d2 = this->read_vector();
    const Vector d3 = this->read_vector();
    std::array<int,2> res = this->read_resolution();

    return {Base(center, d1, d2, d3), res};
    
}

int SceneFile::read_header(const std::string& expected) const
{
    const std::string line = this->read_line();
    const std::vector<std::string> tokens = split(line, ' ');

    if (tokens.size() != 2)
        throw std::invalid_argument("The header must have 2 parameters");
    if (tokens[0] != expected)
        throw std::invalid_argument("The header must start with " + expected);

    return std::stoi(tokens[1]);
}

SpectralColor SceneFile::read_color() const
{
    const std::string line = this->read_line();
    const std::vector<std::string> tokens = split(line, ' ');

    if (tokens[0] == "RGB")
        return  SpectralColor(SC3{std::stod(tokens[1]), std::stod(tokens[2]), std::stod(tokens[3])});

    if (tokens[0] == "SC1")
        return SpectralColor(std::stod(tokens[1]));

    if (tokens[0] == "SC8")
        return SpectralColor(
            SC8{   
                std::stod(tokens[1]), std::stod(tokens[2]), std::stod(tokens[3]), std::stod(tokens[4]), 
                std::stod(tokens[5]), std::stod(tokens[6]), std::stod(tokens[7]), std::stod(tokens[8])
            }
            );

    if (tokens[0] == "SC16")
        return SpectralColor(
            SC16{   
                std::stod(tokens[1]), std::stod(tokens[2]), std::stod(tokens[3]), std::stod(tokens[4]), 
                std::stod(tokens[5]), std::stod(tokens[6]), std::stod(tokens[7]), std::stod(tokens[8]),
                std::stod(tokens[9]), std::stod(tokens[10]), std::stod(tokens[11]), std::stod(tokens[12]),
                std::stod(tokens[13]), std::stod(tokens[14]), std::stod(tokens[15]), std::stod(tokens[16])
            }
        );

    if (tokens[0] == "SC32")
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

    throw std::invalid_argument("The color type must be RGB or Spectrum");
}

std::shared_ptr<BRDF> SceneFile::read_brdf() const
{
    const std::string line = this->read_line();

    if (line == "diffuse")
        return std::make_unique<DiffuseBRDF>(this->read_color());

    if (line == "specular")
        return std::make_unique<SpecularBRDF>(this->read_color());

    if (line == "absorption")
        return std::make_unique<AbsorptionBRDF>();

    if (line == "refractive")
    {
        SpectralColor c = this->read_color();
        double refractive_index = std::stod(this->read_line());
        return std::make_unique<RefractiveBRDF>(c, refractive_index);
    }

    if (line == "roulette")
    {
        int n_brdfs = std::stoi(this->read_line());
        std::vector<std::shared_ptr<BRDF>> brdfs;
        std::vector<double> weights;
        for (int i = 0; i < n_brdfs; i++)
        {
            brdfs.push_back(this->read_brdf());
            weights.push_back(std::stod(this->read_line()));
        }
        return std::make_unique<RouletteBRDF>(brdfs, weights);
    }

    throw std::invalid_argument("The BRDF type must be Diffuse");
}

void SceneFile::read_properties()
{
    int n_properties = this->read_header("Properties");
    for (int i = 0; i < n_properties; i++)
    {
        std::string name,line;
        name = this->read_line();
        std::shared_ptr<BRDF> b = this->read_brdf();
        this->_ch[name] = Property(b);
    }
}

Property SceneFile::read_property(const std::string& key) const
{
    if (this->_ch.find(key) == this->_ch.end())
        throw std::invalid_argument("The property " + key + " does not exist");
    PropertyHash ph = this->_ch;
    return ph[key];
}


std::shared_ptr<Geometry> SceneFile::read_plane(const Property& p) const
{
    Vector normal = this->read_vector();

    std::string line = this->read_line();
    double d = std::stod(line);

    return std::make_shared<Plane>(normal, d, p);
}

std::shared_ptr<Geometry> SceneFile::read_sphere(const Property& p) const
{
    Point center = this->read_point();
    double r = std::stod(this->read_line());
    return std::make_shared<Sphere>(center, r, p);
}

std::shared_ptr<Geometry> SceneFile::read_cylinder(const Property& p) const
{
    Point center = this->read_point();
    double r = std::stod(this->read_line());
    Vector h = this->read_vector();
    return std::make_shared<Cylinder>(center, r, h, p);
}

std::array<double,6> SceneFile::read_bounding_box() const
{
    const std::string line = this->read_line();
    const std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 6)
        throw std::invalid_argument("The bounding box must have 6 parameters");
    return {std::stod(tokens[0]), std::stod(tokens[1]), std::stod(tokens[2]), std::stod(tokens[3]), std::stod(tokens[4]), std::stod(tokens[5])};
}

std::shared_ptr<Geometry> SceneFile::read_mesh(const Property& p) const
{
    const std::string file =  this->_ply_dir + "/" +  this->read_line();
    const std::array<double,6> bb = this->read_bounding_box();
    auto ply = PlyFile(file, p);
    ply.change_bounding_box(bb);
    return ply.to_mesh();
}

std::shared_ptr<Geometry> SceneFile::read_box(const Property& p) const
{
    Point center = this->read_point();
    std::array<Vector,3> axis = {this->read_vector(), this->read_vector(), this->read_vector()};
    return std::make_shared<Box>(center, axis, p);
}

std::shared_ptr<Geometry> SceneFile::read_face(const Property& p) const
{
    Vector normal = this->read_vector();
    Vector u = this->read_vector();
    Vector v = this->read_vector();
    Point point = this->read_point();
    return std::make_shared<Face>(normal, u, v, point, p);
}

std::shared_ptr<Geometry> SceneFile::read_cone(const Property& p) const
{
    Point center = this->read_point();
    Vector axe = this->read_vector();
    double r = std::stod(this->read_line());
    return std::make_shared<Cone>(center, axe, r, p);
}

std::shared_ptr<Geometry> SceneFile::read_disk(const Property& p) const
{
    Point center = this->read_point();
    Vector normal = this->read_vector();
    double r = std::stod(this->read_line());
    return std::make_shared<Disk>(center, normal, r, p);
}

std::shared_ptr<Geometry> SceneFile::read_ellipsoid(const Property& p) const
{
    double a = std::stod(this->read_line());
    double b = std::stod(this->read_line());
    double c = std::stod(this->read_line());
    Point center = this->read_point();
    return std::make_shared<Ellipsoid>(a, b, c, center, p);
}

std::shared_ptr<Geometry> SceneFile::read_triangle(const Property& p) const
{
    auto p1 = std::make_shared<Point>(this->read_point());
    auto p2 = std::make_shared<Point>(this->read_point());
    auto p3 = std::make_shared<Point>(this->read_point());
    return std::make_shared<Triangle>(p1, p2, p3, p);
}

std::shared_ptr<Geometry> SceneFile::read_geometry() const
{
    // Read the type of geometry
    const std::string line = this->read_line();

    // Read the property
    const Property p = this->read_property(this->read_line());

    // Create the appropriate object
    if (line == "plane")
        return this->read_plane(p);
    if(line == "sphere")
        return this->read_sphere(p);
    if(line == "cylinder")
        return this->read_cylinder(p);
    if(line == "mesh")
        return this->read_mesh(p);
    if(line == "box")
        return this->read_box(p);
    if(line == "face")
        return this->read_face(p);
    if(line == "cone")
        return this->read_cone(p);
    if(line == "disk")
        return this->read_disk(p);
    if(line == "ellipsoid")
        return this->read_ellipsoid(p);
    if(line == "triangle")
        return this->read_triangle(p);

    throw std::invalid_argument("The geometry type is unknown");
}

VectorGeometries SceneFile::read_geometries() const
{
    // Read header and number of geometries
    const int n_geometries = this->read_header("Geometries");
    VectorGeometries g;

    // Read all geometries
    for (int i = 0; i < n_geometries; i++)
        g.push_back(this->read_geometry());

    return g;   
}

SceneFile::SceneFile(const std::string& file, std::string ply_dir):
    _ply_dir(std::move(ply_dir))
{
    this->_file.open(file);
    if (!this->_file.is_open())
        throw std::invalid_argument("The file " + file + " does not exist");
}

void SceneFile::read_lights(VectorPunctualLight& pl, VectorAreaLight& al) const
{
    // Read header and number of lights
    const int n_lights = this->read_header("Lights");

    // Read all lights
    for (int i = 0; i < n_lights; i++)
    {
        if (std::string name = this->read_line(); name == "punctual")
            pl.push_back(this->read_punctual_light());
        else if (name == "area")
            al.push_back(this->read_area_light()); 
        else
            throw std::invalid_argument("Unknown light type.");
    }
}

std::shared_ptr<PunctualLight> SceneFile::read_punctual_light() const
{
    SpectralColor power = this->read_color();
    Point center = this->read_point();
    return std::make_shared<PunctualLight>(center, power);
}

std::shared_ptr<AreaLight> SceneFile::read_area_light() const
{
    // Read the geometry
    std::shared_ptr<Geometry> g = this->read_geometry();

    // Create the area light
    return std::make_shared<AreaLight>(g, g->get_properties().get_color());
}

std::unique_ptr<ToneMapping> SceneFile::read_gamma_tm(double max) const
{
    const std::string line = this->read_line();
    const std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 2)
        throw std::invalid_argument("The gamma tone mapping must have 1 parameter");
    double gamma = std::stod(tokens[0]);
    double L;
    if(tokens[1] == "max")
        L = max;
    else
        L = std::stod(tokens[1]);
    
    return std::make_unique<Gamma>(gamma,L);
}

std::unique_ptr<ToneMapping> SceneFile::read_tone_mapping(double max) const
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


void SceneFile::read_scene(const std::string& path, const std::string& file_save)
{
    Camera c = this->read_camera();
    this->read_properties();
    VectorGeometries g = this->read_geometries();
    VectorPunctualLight pl;
    VectorAreaLight al;
    this->read_lights(pl, al);
    auto s = Scene(g, pl, al, c);
    auto rend = Render(s);

    ColorMap cm = rend.render_scene();
    double max = cm.max();
    auto ppm = PpmFile(cm, max, max, rend.get_resolution(), "P3");
    
    ppm.save(path + "/" + "no_tm_" + file_save);

    std::unique_ptr<ToneMapping> t = this->read_tone_mapping(ppm.get_max_range());
    PpmFile ppm_tm = ppm.apply_tone_mapping(t, 255);
    ppm_tm.save(path + "/" + file_save);
}