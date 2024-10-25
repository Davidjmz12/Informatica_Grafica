# Define las bibliotecas individuales
add_library(spatial_element spatial_element.cpp)
target_include_directories(spatial_element PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(point point.cpp)
target_link_libraries(point PUBLIC spatial_element)  
target_include_directories(point PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(vector vector.cpp)
target_link_libraries(vector PUBLIC point)  
target_include_directories(vector PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(matrix matrix.cpp)
target_link_libraries(matrix PUBLIC spatial_element vector point)
target_include_directories(matrix PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(linear_map linear_map.cpp)
target_link_libraries(linear_map PUBLIC base matrix)
target_include_directories(linear_map PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(base base.cpp)
target_link_libraries(base PUBLIC matrix linear_map)
target_include_directories(base PUBLIC ${CMAKE_SOURCE_DIR}/include)

