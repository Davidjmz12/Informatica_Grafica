add_subdirectory(geometry)
add_subdirectory(spatial_element)
add_subdirectory(global_config)
add_subdirectory(properties)
add_subdirectory(files)
add_subdirectory(color)

# ------------------------------------------------------------------------------
# Main executable
add_executable(main main.cpp)
target_link_libraries(main PUBLIC ppm_file scene geometry ply_file global_config)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_definitions(main PUBLIC ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets")

# ------------------------------------------------------------------------------
# Rays

add_library(intersection intersection.cpp)
target_link_libraries(intersection PUBLIC spatial_element point vector property)
target_include_directories(intersection PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(ray ray.cpp)
target_link_libraries(ray PUBLIC intersection)
target_include_directories(ray PUBLIC ${CMAKE_SOURCE_DIR}/include)


add_library(scene scene.cpp)
target_link_libraries(scene PUBLIC camera)
target_include_directories(scene PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(camera camera.cpp)
target_link_libraries(camera PUBLIC ray color_map base geometry light)
target_include_directories(camera PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(light light.cpp)
target_link_libraries(light PUBLIC geometry)
target_include_directories(light PUBLIC ${CMAKE_SOURCE_DIR}/include)

# ------------------------------------------------------------------------------


add_executable(testing testing.cpp)
target_link_libraries(testing PUBLIC spectral_color)
target_include_directories(testing PUBLIC ${CMAKE_SOURCE_DIR}/include)