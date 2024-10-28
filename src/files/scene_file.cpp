#include "files/scene_file.hpp"

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
    std::string line;
    std::getline(this->file, line);
    std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 2)
        throw std::invalid_argument("The resolution must have 2 parameters");
    return {std::stoi(tokens[0]), std::stoi(tokens[1])};
}

Point SceneFile::read_point() const
{
    std::string line;
    std::getline(this->file, line);
    std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 3)
        throw std::invalid_argument("The point must have 3 parameters");
    return Point(std::stod(tokens[0]), std::stod(tokens[1]), std::stod(tokens[2]));
}

Vector SceneFile::read_vector() const
{
    std::string line;
    std::getline(this->file, line);
    std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 3)
        throw std::invalid_argument("The vector must have 3 parameters");
    return Vector(std::stod(tokens[0]), std::stod(tokens[1]), std::stod(tokens[2]));
}

Camera SceneFile::read_camera() const
{
    std::string line;
    std::getline(this->file, line);
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
    std::string line;
    std::getline(this->file, line);
    std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 2)
        throw std::invalid_argument("The header must have 2 parameters");
    if (tokens[0] != expected)
        throw std::invalid_argument("The header must start with " + expected);
    return std::stoi(tokens[1]);
}

SpectralColor SceneFile::read_color() const
{

    if (tokens[1] == "RGB")
        return  SpectralColor(SC3{std::stod(tokens[2]), std::stod(tokens[3]), std::stod(tokens[4])});
    else if (tokens[1] == "SC1")
        return SpectralColor(std::stod(tokens[2]));
    else if (tokens[1] == "SC8")
        return SpectralColor(SC8{std::stod(tokens[2]), std::stod(tokens[3]), std::stod(tokens[4]), std::stod(tokens[5]), 
                                            std::stod(tokens[6]), std::stod(tokens[7]), std::stod(tokens[8]), std::stod(tokens[9])});
    else if (tokens[1] == "SC16")
        return SpectralColor(SC16{std::stod(tokens[2]), std::stod(tokens[3]), std::stod(tokens[4]), std::stod(tokens[5]), 
                                            std::stod(tokens[6]), std::stod(tokens[7]), std::stod(tokens[8]), std::stod(tokens[9]),
                                            std::stod(tokens[10]), std::stod(tokens[11]), std::stod(tokens[12]), std::stod(tokens[13]),
                                            std::stod(tokens[14]), std::stod(tokens[15]), std::stod(tokens[16]), std::stod(tokens[17])});
    else if (tokens[1] == "SC32")
        return SpectralColor(SC32{std::stod(tokens[2]), std::stod(tokens[3]), std::stod(tokens[4]), std::stod(tokens[5]), 
                                            std::stod(tokens[6]), std::stod(tokens[7]), std::stod(tokens[8]), std::stod(tokens[9]),
                                            std::stod(tokens[10]), std::stod(tokens[11]), std::stod(tokens[12]), std::stod(tokens[13]),
                                            std::stod(tokens[14]), std::stod(tokens[15]), std::stod(tokens[16]), std::stod(tokens[17]),
                                            std::stod(tokens[18]), std::stod(tokens[19]), std::stod(tokens[20]), std::stod(tokens[21]),
                                            std::stod(tokens[22]), std::stod(tokens[23]), std::stod(tokens[24]), std::stod(tokens[25]),
                                            std::stod(tokens[26]), std::stod(tokens[27]), std::stod(tokens[28]), std::stod(tokens[29]),
                                            std::stod(tokens[30]), std::stod(tokens[31]), std::stod(tokens[32]), std::stod(tokens[33])});
    else
        throw std::invalid_argument("The color type must be RGB or Spectrum");
}

PropertyHash SceneFile::read_properties() const
{
    int n_colors = this->read_header("Properties");
    PropertyHash ch;
    for (int i = 0; i < n_colors; i++)
    {
        std::string line;
        std::getline(this->file, line);
        std::vector<std::string> tokens = split(line, ' ');
        if (tokens.size() < 3)
            throw std::invalid_argument("The color must have name, type and value");

    }
    return ch;
}

Geometry* SceneFile::read_plane(ColorHash ch) const
{
    Vector normal = this->read_vector();

    std::string line;
    std::getline(this->file, line);
    double d = std::stod(line);
    std::getline(this->file, line);
    if (ch.find(line) == ch.end())
        throw std::invalid_argument("The color " + line + " does not exist");
    SpectralColor color = ch[line];


}

std::vector<Geometry*> SceneFile::read_geometries(ColorHash ch) const
{
    int n_geometries = this->read_header("Geometries");
    std::vector<Geometry*> g;
    for (int i = 0; i < n_geometries; i++)
    {
        std::string line;
        if (line == "plane")
        {
            g.push_back(this->read_plane(ch));
        }
        else
            throw std::invalid_argument("The geometry type must be Plane, Sphere, Cone or Ply");
    }
    return g;   
}

SceneFile::SceneFile(std::string file)
{
    this->file.open(file);
    if (!this->file.is_open())
        throw std::invalid_argument("The file " + file + " does not exist");
}

void SceneFile::read_scene(std::string file_save) const
{
    Camera c = this->read_camera();
    ColorHash ch = this->read_properties();
    std::vector<Geometry*> g = this->read_geometries(ch);
    std::vector<Light> l = this->read_lights();
    ToneMapping* t = this->read_tone_mapping();

    Scene s = Scene(g, l, c);
    PpmFile ppm = PpmFile(s);
    ppm = ppm.apply_tone_mapping(t, 255);
    ppm.save(file_save);
}