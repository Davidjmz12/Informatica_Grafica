add_library(ply_file ply_file.cpp)
target_link_libraries(ply_file PUBLIC triangle mesh)
target_include_directories(ply_file PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(ppm_file ppm_file.cpp)
target_link_libraries(ppm_file PUBLIC color_map tone_mapping_lib)
target_include_directories(ppm_file PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(scene_file scene_file.cpp)
target_link_libraries(scene_file PUBLIC ppm_file photon_mapping direct_photon_mapping explicit_photon_mapping ray_tracing geometry ply_file global_config area_light_lib brdf kernel_density)
target_include_directories(scene_file PUBLIC ${CMAKE_SOURCE_DIR}/include)