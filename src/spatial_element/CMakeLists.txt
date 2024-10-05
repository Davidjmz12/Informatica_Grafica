# Define las bibliotecas individuales
add_library(spatial_element spatial_element.cpp)

add_library(point point.cpp)
target_link_libraries(point PUBLIC spatial_element)  # point depende de spatial_element

add_library(vector vector.cpp)
target_link_libraries(vector PUBLIC spatial_element point)  # vector depende de spatial_element y point

# Directorios de cabecera
target_include_directories(spatial_element PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(point PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(vector PUBLIC ${CMAKE_SOURCE_DIR}/include)
