#include "files/ply_file.hpp"

PlyFile::PlyFile(VectorGeometries elements, std::array<double,6> bounding_box)
    : _elements(elements), _bounding_box(bounding_box)
{}

PlyFile::PlyFile(std::string file_path, Property properties)
{
    std::ifstream file(file_path);
    if(!file.is_open())
        throw std::runtime_error("Could not open file: " + file_path);
    
    size_t num_vertices, num_faces;
    if (!read_header(file, num_vertices, num_faces))
        throw std::runtime_error("Invalid header");

    std::vector<std::shared_ptr<Point>> points;
    double x_min, x_max, y_min, y_max, z_min, z_max;
    for(size_t i = 0; i < num_vertices; i++)
    {
        double x, y, z;
        file >> x >> y >> z;
        x_min = std::min(x_min, x); x_max = std::max(x_max, x); 
        y_min = std::min(y_min, y); y_max = std::max(y_max, y);
        z_min = std::min(z_min, z); z_max = std::max(z_max, z);
        points.push_back(std::make_shared<Point>(x,y,z));
        std::string rest_of_line;
        std::getline(file, rest_of_line);
    }

    
    
    std::vector<std::shared_ptr<Geometry>> elements;

    for(size_t i=0; i< num_faces; i++)
    {
        size_t n_vertex_face; 
        size_t p0,p1,p2,p3;
        
        file >> n_vertex_face;
        if(n_vertex_face == 3)
        {
            file >> p0 >> p1 >> p2;
            try{
                std::shared_ptr<Geometry> triangle = std::make_shared<Triangle>(points[p0],points[p1],points[p2],properties);
                elements.push_back(triangle);
            } catch (std::invalid_argument& e){}
        } else
        {
            throw std::runtime_error("Only supported triangles and faces");
        }
    }

    this->_elements = elements;
    this->_bounding_box = {x_min, x_max, y_min, y_max, z_min, z_max};
    
}


bool PlyFile::read_header(std::ifstream& file, size_t& num_vertices, size_t& num_faces)
{
    std::string line;
    size_t wanted_headers = 3;
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

VectorGeometries PlyFile::get_elements() const
{
    return this->_elements;
}

std::array<double,6> PlyFile::get_bounding_box() const
{
    return this->_bounding_box;
}

double PlyFile::standardize(double value, double min, double max) const
{
    return max!=min?(value-min)/(max-min):0;
}

PlyFile PlyFile::change_bounding_box(std::array<double,6> new_bounding_box)
{
    auto x_op = [new_bounding_box,this](double x){return this->standardize(x,this->_bounding_box[0], this->_bounding_box[1])*(new_bounding_box[1]-new_bounding_box[0])+new_bounding_box[0];};
    auto y_op = [new_bounding_box,this](double y){return this->standardize(y,this->_bounding_box[2], this->_bounding_box[3])*(new_bounding_box[3]-new_bounding_box[2])+new_bounding_box[2];};
    auto z_op = [new_bounding_box,this](double z){return this->standardize(z,this->_bounding_box[4], this->_bounding_box[5])*(new_bounding_box[5]-new_bounding_box[4])+new_bounding_box[4];};

    VectorGeometries new_elements;
    for(auto element: this->_elements)
    {
        Triangle el_trig = *std::static_pointer_cast<Triangle>(element);
        try{
           std::shared_ptr<Geometry> new_element = std::make_shared<Triangle>(Point(x_op(el_trig[0][0]),y_op(el_trig[0][1]),z_op(el_trig[0][2])),
                                        Point(x_op(el_trig[1][0]),y_op(el_trig[1][1]),z_op(el_trig[1][2])),
                                        Point(x_op(el_trig[2][0]),y_op(el_trig[2][1]),z_op(el_trig[2][2])),
                                        el_trig.get_properties());
            new_elements.push_back(new_element);
        } catch (std::invalid_argument& e){}

    }

    return PlyFile(new_elements, new_bounding_box);
}

std::shared_ptr<Geometry> PlyFile::to_mesh() const
{
    return std::make_shared<Mesh>(this->_elements);
}

std::ostream& operator<<(std::ostream& os, const PlyFile& ply_file)
{
    os << ply_file.to_string();
    return os;
}

std::string PlyFile::to_string() const
{
    std::string str = "PlyFile: ";
    for(auto element: this->_elements)
        str += element->to_string() + "\n";
    return str;
}
