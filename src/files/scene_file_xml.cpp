#include "files/scene_file_xml.hpp"

SceneFile::SceneFile(const std::string& file, std::string ply_dir):
    _ply_dir(ply_dir)
{
    XmlReader reader;
    this->_root = reader.parse(file);
}

void SceneFile::read_scene(const std::string& path)
{

    Camera c = this->read_camera();
    _ch = this->read_properties();

    VectorGeometries g = this->read_geometries();
    VectorPunctualLight pl = this->read_punctual_lights();
    VectorAreaLight al = this->read_area_lights();

    auto s = Scene(g, pl, al, c);
    
    Render* rend = this->read_render_type(s);

    ColorMap cm = rend->render_scene();
    double max = cm.max();
    auto ppm = PpmFile(cm, max, max, rend->get_resolution(), "P3");
    
    std::regex re(".ppm");
    std::string file_save = std::regex_replace(path, re, "_no_tm.ppm");
    ppm.save(file_save);

    std::unique_ptr<ToneMapping> t = this->read_tone_mapping(ppm.get_max_range());
    PpmFile ppm_tm = ppm.apply_tone_mapping(t, 255);
    ppm_tm.save(path);
}

std::array<double,6> read_bounding_box(std::string line)
{
    const std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 6)
        throw std::invalid_argument("The bounding box must have 6 parameters");
    return {std::stod(tokens[0]), std::stod(tokens[1]), std::stod(tokens[2]), std::stod(tokens[3]), std::stod(tokens[4]), std::stod(tokens[5])};
}


// ------------------------------------------------------------
// ------------------ Auxiliary functions ---------------------
// ------------------------------------------------------------

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


Point read_point(XmlNode node, std::string id, bool required = true, Point default_value = Point())
{
    if(!node.hasChild(id) && !required)
        return default_value;
    
    if(!node.hasChild(id) && required)
        throw std::invalid_argument("The point " + id + " must be defined");

    std::string line = node.getContentChild(id);
    const std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 3)
        throw std::invalid_argument("The point must have 3 parameters");
    return {std::stod(tokens[0]), std::stod(tokens[1]), std::stod(tokens[2])};
}

Vector read_vector(XmlNode node, std::string id, bool required = true, Vector default_value = Vector())
{
    if(!node.hasChild(id) && !required)
        return default_value;
    
    if(!node.hasChild(id) && required)
        throw std::invalid_argument("The vector " + id + " must be defined");

    std::string line = node.getContentChild(id);
    const std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 3)
        throw std::invalid_argument("The vector must have 3 parameters");
    return {std::stod(tokens[0]), std::stod(tokens[1]), std::stod(tokens[2])};
}

std::array<int, 2> read_resolution(std::string line)
{
    const std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 2)
        throw std::invalid_argument("The resolution must have 2 parameters");
    return {std::stoi(tokens[0]), std::stoi(tokens[1])};
}

Color read_color(XmlNode node, std::string id, bool required = true, Color default_value = Color())
{
    if(!node.hasChild(id) && !required)
        return default_value;
    
    if(!node.hasChild(id) && required)
        throw std::invalid_argument("The color " + id + " must be defined");

    std::string line = node.getContentChild(id);
    const std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 3)
        throw std::invalid_argument("The color must have 3 parameters");
    return Color(SC3{std::stod(tokens[0]), std::stod(tokens[1]), std::stod(tokens[2])});
}

double read_double(XmlNode node, std::string id, bool required = true, double default_value = 0)
{
    if(!node.hasChild(id) && !required)
        return default_value;
    
    if(!node.hasChild(id) && required)
        throw std::invalid_argument("The double " + id + " must be defined");

    std::string line = node.getContentChild(id);
    return std::stod(line);
}

int read_int(XmlNode node, std::string id, bool required = true, int default_value = 0)
{
    if(!node.hasChild(id) && !required)
        return default_value;
    
    if(!node.hasChild(id) && required)
        throw std::invalid_argument("The int " + id + " must be defined");

    std::string line = node.getContentChild(id);
    return std::stoi(line);
}

std::shared_ptr<BRDF> read_BRDF(XmlNode node)
{
    Color kd = read_color(node, "kd", false, Color());
    Color ks = read_color(node, "ks", false, Color());
    Color kt = read_color(node, "kt", false, Color());
    Color ke = read_color(node, "ke", false, Color());
    double refraction_index = read_double(node, "refraction_index", false, 1);
    return std::make_shared<BRDF>(kd, ks, kt, refraction_index, ke);
}


std::shared_ptr<Geometry> read_geometry(std::string type, std::shared_ptr<BRDF> p, XmlNode node, std::string ply_dir)
{
    if(type == "Plane")
    {
        Vector normal = read_vector(node, "normal");
        double d = read_double(node, "d", 0, false);
        return std::make_shared<Plane>(normal, d, p);
    }
    else if(type == "Sphere")
    {
        Point center = read_point(node, "center");
        double r = read_double(node, "r", 0, false);
        return std::make_shared<Sphere>(center, r, p);
    }
    else if(type == "Cylinder")
    {
        Point center = read_point(node, "center");
        double r = read_double(node, "r", 0, false);
        Vector h = read_vector(node, "h");
        return std::make_shared<Cylinder>(center, r, h, p);
    }
    else if(type == "Mesh")
    {
        const std::string ply_file = ply_dir + "/" + node.getContentChild("ply_file");
        auto ply = PlyFile(ply_file, p);
        if(node.hasChild("bounding_box"))
        {
            std::array<double,6> bb = read_bounding_box(node.getContentChild("bounding_box"));
            ply.change_bounding_box(bb);
        }
        return ply.to_mesh();
    }
    else if(type == "Box")
    {
        Point center = read_point(node, "center");
        Vector x = read_vector(node, "x");
        Vector y = read_vector(node, "y");
        Vector z = read_vector(node, "z");
        std::array<Vector,3> axis = {x, y, z};
        return std::make_shared<Box>(center, axis, p);
    }
    else if(type == "Face")
    {
        Vector normal = read_vector(node, "normal");
        Vector u = read_vector(node, "u");
        Vector v = read_vector(node, "v");
        Point center = read_point(node, "center");
        return std::make_shared<Face>(normal, u, v, center, p);
    }
    else if(type == "Cone")
    {
        Point center = read_point(node, "center");
        double r = read_double(node, "r");
        Vector axe = read_vector(node, "axe");
        return std::make_shared<Cone>(center, axe, r, p);
    }
    else if(type == "Disk")
    {
        Point center = read_point(node, "center");
        Vector normal = read_vector(node, "normal");
        double r = read_double(node, "r");
        return std::make_shared<Disk>(center, normal, r, p);
    }
    else if(type == "Ellipsoid")
    {
        Point center = read_point(node, "center");
        double a = read_double(node, "a", 0, false);
        double b = read_double(node, "b", 0, false);
        double c = read_double(node, "c", 0, false);
        return std::make_shared<Ellipsoid>(a, b, c, center, p);
    }
    else if(type == "Triangle")
    {
        Point p1 = read_point(node, "p1");
        Point p2 = read_point(node, "p2");
        Point p3 = read_point(node, "p3");
        return std::make_shared<Triangle>(p1, p2, p3, p);
    }
    else
    {
        throw std::invalid_argument("Unknown geometry type.");
    }
    
}

Render* read_photon_mapping(XmlNode& node, Scene& s)
{
    int n_photons = read_int(node, "n_photons", false, 100000);
    int n_neighbours = read_int(node, "n_neighbours", false, 1000);
    double radius = read_double(node, "radius", false, 0.1);
    std::unique_ptr<Kernel> kernel = read_kernel(node);
    std::string type = node.getContentChild("type");

    if (type == "explicit")
        return new ExplicitPhotonMapping(s, n_photons, n_neighbours, radius, std::move(kernel));
    else if (type == "direct")
        return new DirectPhotonMapping(s, n_photons, n_neighbours, radius, std::move(kernel));

}

std::unique_ptr<Kernel> read_kernel(XmlNode& node)
{
    XmlNode kernel = node.getChild("Kernel");
    std::string type = kernel.getAttribute("type");
    if (type == "gaussian")
    {
        double sigma = read_double(node, "sigma", false, 0.1);
        return std::make_unique<GaussKernel>(sigma);
    }
    else if (type == "cone")
    {
        return std::make_unique<ConeKernel>();
    }
    else if (type == "constant")
    {
        return std::make_unique<ConstantKernel>();
    }
    else
    {
        throw std::invalid_argument("Kernel type not recognized");
    }
}

double read_V_tm(XmlNode& node, double max)
{
    std::string line = node.getContentChild("L");
    if(line == "max")
        return max;
    return std::stod(line);
}


// ------------------------------------------------------------
// ---------------------- Private methods ---------------------
// ------------------------------------------------------------


Camera SceneFile::read_camera() const
{
    XmlNode camera = this->_root.getChild("Camera");
    Point center = read_point(camera, "center");
    Vector left = read_vector(camera, "left");
    Vector up = read_vector(camera, "up");
    Vector front = read_vector(camera, "front");
    std::array<int,2> resolution = read_resolution(camera.getContentChild("resolution"));

    return {Base(center, left, up, front), resolution};
}

BRDFHash SceneFile::read_properties() const
{
    BRDFHash ch;
    std::vector<XmlNode> properties_children = this->_root.getChildren("Property");
    for (auto property : properties_children)
    {
        std::string name = property.getAttribute("name");
        std::shared_ptr<BRDF> b = read_BRDF(property);

        ch[name] = b;
    }
    return ch;
}

VectorGeometries SceneFile::read_geometries() const
{
    VectorGeometries geometries;
    std::vector<XmlNode> geometries_children = this->_root.getChildren("Geometry");
    BRDFHash ch = this->_ch;
    for (auto geometry : geometries_children)
    {   
        // Dont read area-lights
        if(!geometry.hasAttribute("brdf"))
            continue;
        std::string type = geometry.getAttribute("type");
        std::string brdf = geometry.getAttribute("brdf");
        
        auto p = ch[brdf];
        geometries.push_back(read_geometry(type, p, geometry, this->_ply_dir));
    }
    return geometries;
}
VectorPunctualLight SceneFile::read_punctual_lights() const
{
    VectorPunctualLight pl;
    std::vector<XmlNode> punctual_lights_children = this->_root.getChildren("PunctualLight");
    for (auto punctual_light : punctual_lights_children)
    {
        Color power = read_color(punctual_light, "power");
        Point center = read_point(punctual_light, "center");
        pl.push_back(std::make_shared<PunctualLight>(center, power));
    }
    return pl;
}
VectorAreaLight SceneFile::read_area_lights() const
{
    VectorAreaLight al;
    std::vector<XmlNode> area_lights_children = this->_root.getChildren("Geometry");
    for (auto area_light : area_lights_children)
    {
        if(!area_light.hasChild("emission"))
            continue;
        
        std::string type = area_light.getAttribute("type");
        Color emission = read_color(area_light, "emission");

        std::shared_ptr<Geometry> g = read_geometry(type, std::make_shared<BRDF>(), area_light, this->_ply_dir);
        al.push_back(std::make_shared<AreaLight>(g, emission));
    }
    return al;
}

Render* SceneFile::read_render_type(Scene& s) const
{
    XmlNode render = this->_root.getChild("Render");
    std::string type = render.getAttribute("type");
    if (type == "ray-tracing")
        return new RayTracing(s);
    else if (type == "photon-mapping")
        return read_photon_mapping(render, s);
    else
        throw std::invalid_argument("Render type not recognized");
}

std::unique_ptr<ToneMapping> SceneFile::read_tone_mapping(double max) const
{
    XmlNode tone_mapping = this->_root.getChild("ToneMapping");
    std::string type = tone_mapping.getAttribute("type");

    if (type == "gamma")
    {
        double gamma = read_double(tone_mapping, "gamma", false, 2.2);
        double V = read_V_tm(tone_mapping, max);
        return std::make_unique<Gamma>(gamma, V);
    }
    else if(type == "clamping")
        return std::make_unique<Clamping>();
    else if(type == "equalization")
    {
        double V = read_V_tm(tone_mapping, max);
        return std::make_unique<Equalization>(V);
    }
    else if(type == "logarithmic")
    {
        double alpha = read_double(tone_mapping, "alpha", false, 0.1);
        double V = read_V_tm(tone_mapping, max);
        return std::make_unique<Logarithmic>(V, alpha);
    }
    else if(type == "drago")
    {
        double V = read_V_tm(tone_mapping, max);
        return std::make_unique<Drago>(V);
    }
    else
        throw std::invalid_argument("Tone mapping type not recognized");
}