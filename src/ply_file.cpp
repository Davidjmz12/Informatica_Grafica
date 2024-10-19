#include "ply_file.hpp"

PlyFile::PlyFile(std::vector<Triangle> triangles, std::array<double,6> bounding_box)
    : _triangles(triangles), _bounding_box(bounding_box)
{}

PlyFile::PlyFile(std::string file_path)
{
    std::ifstream file(file_path);
    if(!file.is_open())
        throw std::runtime_error("Could not open file: " + file_path);
    
    size_t num_vertices, num_faces;
    if (!read_header(file, num_vertices, num_faces))
        throw std::runtime_error("Invalid header");

    std::vector<Point> points;
    double x_min, x_max, y_min, y_max, z_min, z_max;
    for(size_t i = 0; i < num_vertices; i++)
    {
        double x, y, z;
        x_min = std::min(x_min, x); x_max = std::max(x_max, x); 
        y_min = std::min(y_min, y); y_max = std::max(y_max, y);
        z_min = std::min(z_min, z); z_max = std::max(z_max, z);
        file >> x >> y >> z;
        points.push_back(Point(x,y,z));
    }

    std::vector<Triangle> triangles;

    for(size_t i=0; i< num_faces; i++)
    {
        size_t n_vertex_face; 
        size_t p0,p1,p2;
        file >> n_vertex_face >> p0 >> p1 >> p2;
        if(n_vertex_face != 3)
            throw std::runtime_error("Only triangles supported");
        triangles.push_back(Triangle(points[p0],points[p1],points[p2],Property()));
    }

    this->_triangles = triangles;
    this->_bounding_box = {x_min, x_max, y_min, y_max, z_min, z_max};
    
}


bool PlyFile::read_header(std::ifstream& file, size_t& num_vertices, size_t& num_faces)
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

std::array<double,6> PlyFile::get_bounding_box() const
{
    return this->_bounding_box;
}

double PlyFile::standarize(double value, double min, double max) const
{
    return (value-min)/(max-min);
}

PlyFile PlyFile::change_bounding_box(std::array<double,6> new_bounding_box)
{
    auto x_op = [new_bounding_box,this](double x){return this->standarize(x,this->_bounding_box[0], this->_bounding_box[1])*(new_bounding_box[1]-new_bounding_box[0])+new_bounding_box[0];};
    auto y_op = [new_bounding_box,this](double y){return this->standarize(y,this->_bounding_box[2], this->_bounding_box[3])*(new_bounding_box[3]-new_bounding_box[2])+new_bounding_box[2];};
    auto z_op = [new_bounding_box,this](double z){return this->standarize(z,this->_bounding_box[4], this->_bounding_box[5])*(new_bounding_box[5]-new_bounding_box[4])+new_bounding_box[4];};

    std::vector<Triangle> new_triangles;
    for(auto triangle:this->_triangles)
    {
        Triangle new_tr = Triangle(Point(x_op(triangle[0][0]),y_op(triangle[0][1]),z_op(triangle[0][2])),
                                    Point(x_op(triangle[1][0]),y_op(triangle[1][1]),z_op(triangle[1][2])),
                                    Point(x_op(triangle[2][0]),y_op(triangle[2][1]),z_op(triangle[2][2])),
                                    Property());
        new_triangles.push_back(new_tr);
    }

    return PlyFile(new_triangles, new_bounding_box);

}

std::string PlyFile::to_string() const
{
    std::string str = "PlyFile: ";
    for(auto triangle: this->_triangles)
        str += triangle.to_string() + "\n";
    return str;
}
