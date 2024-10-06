add_subdirectory(geometry)
add_subdirectory(tone_mapping)
add_subdirectory(spatial_element)


# Main executable
add_executable(main main.cpp)

# Libraries
add_library(matrix matrix.cpp)
target_link_libraries(matrix PUBLIC spatial_element vector point)

add_library(linear_map linear_map.cpp)
target_link_libraries(linear_map PUBLIC base matrix)

add_library(base base.cpp)
target_link_libraries(base PUBLIC matrix linear_map)

add_library(planet planet.cpp)
target_link_libraries(planet PUBLIC base)


# Images

add_library(color color.cpp)
target_link_libraries(color PUBLIC tone_mapping)

add_library(color_map color_map.cpp)
target_link_libraries(color_map PUBLIC color)

add_library(ppm_file ppm_file.cpp)
target_link_libraries(ppm_file PUBLIC color_map)


# Rays

add_library(intersection intersection.cpp)
target_link_libraries(intersection PUBLIC spatial_element point vector)

add_library(ray ray.cpp)
target_link_libraries(ray PUBLIC intersection)



add_library(ply_file ply_file.cpp)
target_link_libraries(ply_file PUBLIC triangle)

# Include directories
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(base PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(linear_map PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(matrix PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(planet PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(color PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(color_map PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(ppm_file PUBLIC ${CMAKE_SOURCE_DIR}/include)


# RAYS
target_include_directories(ray PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(intersection PUBLIC ${CMAKE_SOURCE_DIR}/include)
