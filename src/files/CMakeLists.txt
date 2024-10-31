
add_library(ply_file ply_file.cpp)
target_link_libraries(ply_file PUBLIC triangle mesh)
target_include_directories(ply_file PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(ppm_file ppm_file.cpp)
target_link_libraries(ppm_file PUBLIC color_map tone_mapping_lib scene)
target_include_directories(ppm_file PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(scene_file scene_file.cpp)
target_link_libraries(scene_file PUBLIC ppm_file render geometry ply_file global_config)
target_include_directories(scene_file PUBLIC ${CMAKE_SOURCE_DIR}/include)