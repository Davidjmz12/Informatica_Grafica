#include "ply_file.hpp"

PlyFile::PlyFile(std::string file_path)
{
    std::ifstream file(file_path);
    if(!file.is_open())
        throw std::runtime_error("Could not open file: " + file_path);
    
    unsigned int num_vertices, num_faces;
    if (!read_header(file, num_vertices, num_faces))
        throw std::runtime_error("Invalid header");

    std::vector<Geometric> points;
    for(unsigned int i = 0; i < num_vertices; i++)
    {
        double x, y, z;
        file >> x >> y >> z;
        points.push_back(Geometric::point(x,y,z));
    }

    std::vector<Triangle> triangles;

    for(unsigned int i=0;i< num_vertices;i++)
    {
        unsigned int n_vertex_face; 
        unsigned int p0,p1,p2;
        file >> n_vertex_face >> p0 >> p1 >> p2;
        if(n_vertex_face != 3)
            throw std::runtime_error("Only triangles supported");
        triangles.push_back(Triangle(points[p0],points[p1],points[p2]));
    }

    this->_triangles = triangles;
    
}


bool PlyFile::read_header(std::ifstream& file, unsigned int& num_vertices, unsigned int& num_faces)
{
    std::string line;
    int wanted_headers = 3;
    while(std::getline(file, line))
    {
        if(std::regex_match(line,std::regex(" *element vertex +[0-9]+")))
        {
            std::smatch match;
            std::regex_search(line, match, std::regex("[0-9]+"));
            num_vertices = std::stoi(match.str());
            wanted_headers--;
        }
        else if(std::regex_match(line,std::regex(" *element face +[0-9]+")))
        {
            std::smatch match;
            std::regex_search(line, match, std::regex("[0-9]+"));
            num_faces = std::stoi(match.str());
            wanted_headers--;
        }
        else if(std::regex_match(line,std::regex(" *end_header *")))
        {
            wanted_headers--;
            break;
        }
    }

    return wanted_headers==0;
}

std::vector<Triangle> PlyFile::get_triangles() const
{
    return this->_triangles;
}