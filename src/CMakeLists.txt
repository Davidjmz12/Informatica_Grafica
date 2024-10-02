add_executable(main main.cpp)
target_link_libraries(main PUBLIC ppm_file)
add_subdirectory(geometry)


# Libraries
add_library(geometric geometric.cpp)

add_library(matrix matrix.cpp)
target_link_libraries(matrix PUBLIC geometric)

add_library(linear_map linear_map.cpp)
target_link_libraries(linear_map PUBLIC base matrix)

add_library(base base.cpp)
target_link_libraries(base PUBLIC matrix linear_map)

add_library(planet planet.cpp)
target_link_libraries(planet PUBLIC base)


# Images

add_library(tone_mapping tone_mapping.cpp)

add_library(color color.cpp)
target_link_libraries(color PUBLIC tone_mapping)

add_library(color_map color_map.cpp)
target_link_libraries(color_map PUBLIC color)

add_library(ppm_file ppm_file.cpp)
target_link_libraries(ppm_file PUBLIC color_map)

add_library(bmp_file bmp_file.cpp)
target_link_libraries(bmp_file PUBLIC color_map)

add_library(tiff_file tiff_file.cpp)
target_link_libraries(tiff_file PUBLIC color_map)

# Rays

add_library(ray ray.cpp)
target_link_libraries(ray PUBLIC geometry)

add_library(intersection intersection.cpp)
target_link_libraries(intersection PUBLIC geometric)



# Include directories
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(base PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(geometric PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(linear_map PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(matrix PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(planet PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(color PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(color_map PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(tone_mapping PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(ppm_file PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_include_directories(bmp_file PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(tiff_file PUBLIC ${CMAKE_SOURCE_DIR}/include)


target_include_directories(ray PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(intersection PUBLIC ${CMAKE_SOURCE_DIR}/include)
