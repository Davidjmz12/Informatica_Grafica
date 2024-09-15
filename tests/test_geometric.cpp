#include "geometric.hpp"

int main()
{
    //Points creation
    Geometric point = Geometric::point(1,2,3);
    
    if (!point.is_point()) {
        std::cout << "ERROR: Crear puntos." << std::endl;
    } else {
        std::cout << "OK: Crear puntos." << std::endl;
    }

    //Vector creation
    Geometric vector = Geometric::vector(1,0,0);
    
    if (!point.is_vector()) {
        std::cout << "ERROR: Crear puntos." << std::endl;
    } else {
        std::cout << "OK: Crear puntos." << std::endl;
    }

    //Equality
    Geometric vector2 = Geometric::vector(1,2,3);

    if (vector2 == point) {
        std::cout << "ERROR: Comparaciones" << std::endl;
    } else {
        std::cout << "OK: Comparaciones" << std::endl;
    }
    
    Geometric v_1 = Geometric::vector(1,2,3);
    Geometric v_2 = Geometric::vector(3,2,1);

    std::cout << "10 = " << v_1.dot(v_2) << std::endl;
    std::cout << "(-4,8,-4) = " << v_1.cross(v_2) << std::endl;

    std::cout << "g[0]" << point[0] << std::endl;
    
    try{
        point[-1];
    } catch(int i){
        
    }

    return 0;
}