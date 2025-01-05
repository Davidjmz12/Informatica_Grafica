#include <utility>

#include "files/ply_file.hpp"

PlyFile::PlyFile(VectorTriangles elements, const std::array<double,6>& bounding_box)
    : _elements(std::move(elements)), _bounding_box(bounding_box)
{}

PlyFile::PlyFile(const std::string& file_path, std::shared_ptr<BRDF> properties)
{
    std::ifstream file(file_path);
    if(!file.is_open())
        throw std::runtime_error("Could not open file: " + file_path);
    
    if (!read_header(file))
        throw std::runtime_error("Invalid header");

    if(!read_points(file))
        throw std::runtime_error("Invalid points");

    if(!read_faces(file, properties))
        throw std::runtime_error("Invalid faces");

}


bool PlyFile::read_points(std::ifstream& file)
{
    PointsVector points;

    double x_min, x_max, y_min, y_max, z_min, z_max;

    size_t pos_x = this->_properties_vertices_map["x"];
    size_t pos_y = this->_properties_vertices_map["y"];
    size_t pos_z = this->_properties_vertices_map["z"];

    for(size_t i = 0; i < this->_num_vertices; i++)
    {
        std::vector<double> properties(this->_properties_vertices_map.size());
        for(size_t j=0; j<this->_properties_vertices_map.size(); j++)
        {
            file >> properties[j];
        }
        double x = properties[pos_x];
        double y = properties[pos_y];
        double z = properties[pos_z];
        x_min = std::min(x_min, x); x_max = std::max(x_max, x);
        y_min = std::min(y_min, y); y_max = std::max(y_max, y);
        z_min = std::min(z_min, z); z_max = std::max(z_max, z);

        double u = 0, v = 0;
        if(this->_has_texture)
        {
            u = properties[this->_properties_vertices_map["s"]];
            v = properties[this->_properties_vertices_map["t"]];
        }
        std::shared_ptr<Point> point = std::make_shared<Point>(x, y, z);
        PointWithTexture point_with_texture = {point, std::make_shared<std::array<double, 2>>(std::array<double, 2>{u, v})};
        points.push_back(point_with_texture);
    }
    this->_points = points;
    this->_bounding_box = {x_min, x_max, y_min, y_max, z_min, z_max};
    return true;
}

bool PlyFile::read_faces(std::ifstream& file, std::shared_ptr<BRDF> properties)
{
    for(size_t i=0; i< this->_num_faces; i++)
    {
        size_t n_vertex_face; 

        file >> n_vertex_face;
        if(n_vertex_face == 3)
        {
            size_t p0,p1,p2;
            file >> p0 >> p1 >> p2;
            try{
                auto triangle = std::make_shared<Triangle>(_points[p0],_points[p1],_points[p2],properties);
                this->_elements.push_back(triangle);
            } catch (std::invalid_argument&){}

        } else
        {
            throw std::runtime_error("Only supported triangles and faces");
        }
    }

    return true;
}

bool PlyFile::read_header(std::ifstream& file)
{
    std::string line;
    int pos_properties = 0;
    bool is_vertex_properties = false;
    while(std::getline(file, line))
    {
        std::smatch match;

        if(std::regex_search(line, match, std::regex(" *element vertex +([0-9]+)")))
        {
            this->_num_vertices = std::stoi(match[1]);
            is_vertex_properties = true;
        }
        else if(std::regex_search(line, match, std::regex(" *element face +([0-9]+)")))
        {
            this->_num_faces = std::stoi(match[1]);
            is_vertex_properties = false;
        }
        else if(std::regex_search(line, match, std::regex(" *property +([a-zA-Z_]+) +([a-zA-Z_]+)")))
        {
            if(is_vertex_properties)
            {
                this->_properties_vertices_map[match[2]] = pos_properties++;
                if(match[2] == "s" || match[2] == "t")
                    this->_has_texture = true;
                
                if(match[2] == "nx" || match[2] == "ny" || match[2] == "nz")
                    this->_has_normals = true;
            }
                
        }
        else if(line == "end_header")
        {
            return true;
        }
    }

    return false;
}

VectorTriangles PlyFile::get_elements() const
{
    return this->_elements;
}

std::array<double,6> PlyFile::get_bounding_box() const
{
    return this->_bounding_box;
}

std::shared_ptr<Geometry> PlyFile::to_mesh() const
{
    std::vector<std::shared_ptr<Geometry>> geometries;

    // Populate geometries with elements from triangles
    for (const auto& triangle : this->_elements) {
        geometries.push_back(triangle);  // Implicitly converts std::shared_ptr<Triangle> to std::shared_ptr<Geometry>
    }

    const size_t depth = GlobalConf::get_instance()->get_max_depth();

    return std::make_shared<Mesh>(geometries, depth);
}

std::ostream& operator<<(std::ostream& os, const PlyFile& ply_file)
{
    os << ply_file.to_string();
    return os;
}

std::string PlyFile::to_string() const
{
    std::string str = "PlyFile: ";
    for(const auto& element: this->_elements)
        str += element->to_string() + "\n";
    return str;
}
