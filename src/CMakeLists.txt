add_subdirectory(geometry)
add_subdirectory(tone_mapping)
add_subdirectory(spatial_element)
add_subdirectory(global_config)

# ------------------------------------------------------------------------------
# Main executable
add_executable(main main.cpp)
target_link_libraries(main PUBLIC ppm_file scene geometry ply_file global_config)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_definitions(main PUBLIC ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets")
# ------------------------------------------------------------------------------
# Planet executable
add_library(matrix matrix.cpp)
target_link_libraries(matrix PUBLIC spatial_element vector point)
target_include_directories(matrix PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(linear_map linear_map.cpp)
target_link_libraries(linear_map PUBLIC base matrix)
target_include_directories(linear_map PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(base base.cpp)
target_link_libraries(base PUBLIC matrix linear_map)
target_include_directories(base PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(planet planet.cpp)
target_link_libraries(planet PUBLIC base)
target_include_directories(planet PUBLIC ${CMAKE_SOURCE_DIR}/include)


# ------------------------------------------------------------------------------
# Images
add_library(color color.cpp)
target_link_libraries(color PUBLIC tone_mapping)
target_include_directories(color PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(color_map color_map.cpp)
target_link_libraries(color_map PUBLIC color)
target_include_directories(color_map PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(ppm_file ppm_file.cpp)
target_link_libraries(ppm_file PUBLIC color_map tone_mapping_lib scene)
target_include_directories(ppm_file PUBLIC ${CMAKE_SOURCE_DIR}/include)

# ------------------------------------------------------------------------------
# Rays

add_library(intersection intersection.cpp)
target_link_libraries(intersection PUBLIC spatial_element point vector property)
target_include_directories(intersection PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(ray ray.cpp)
target_link_libraries(ray PUBLIC intersection)
target_include_directories(ray PUBLIC ${CMAKE_SOURCE_DIR}/include)


add_library(ply_file ply_file.cpp)
target_link_libraries(ply_file PUBLIC triangle mesh)
target_include_directories(ply_file PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(scene scene.cpp)
target_link_libraries(scene PUBLIC camera)
target_include_directories(scene PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(camera camera.cpp)
target_link_libraries(camera PUBLIC ray color_map base geometry)
target_include_directories(camera PUBLIC ${CMAKE_SOURCE_DIR}/include)

# ------------------------------------------------------------------------------


add_executable(testing testing.cpp)
target_include_directories(testing PUBLIC ${CMAKE_SOURCE_DIR}/include)