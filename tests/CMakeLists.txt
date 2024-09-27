
# TEST GEOMETRIC
add_executable(test_geometric test_geometric.cpp)
target_link_libraries(test_geometric PUBLIC geometric)
add_test(NAME test_geometric COMMAND test_geometric)
target_include_directories(test_geometric PUBLIC ${CMAKE_SOURCE_DIR}/include)

# TEST LINEAR MAP
add_executable(test_linear_map test_linear_map.cpp)
target_link_libraries(test_linear_map PUBLIC linear_map base)
add_test(NAME test_linear_map COMMAND test_linear_map)
target_include_directories(test_linear_map PUBLIC ${CMAKE_SOURCE_DIR}/include)

# TEST MATRIX
add_executable(test_matrix test_matrix.cpp)
target_link_libraries(test_matrix PUBLIC matrix)
add_test(NAME test_matrix COMMAND test_matrix)
target_include_directories(test_matrix PUBLIC ${CMAKE_SOURCE_DIR}/include)

# TEST BASE
add_executable(test_base test_base.cpp)
target_link_libraries(test_base PUBLIC base)
add_test(NAME test_base COMMAND test_base)
target_include_directories(test_base PUBLIC ${CMAKE_SOURCE_DIR}/include)


# TEST SPHERE
add_executable(test_sphere test_sphere.cpp)
target_link_libraries(test_sphere PUBLIC sphere)
add_test(NAME test_sphere COMMAND test_sphere)
target_include_directories(test_sphere PUBLIC ${CMAKE_SOURCE_DIR}/include)


# TEST PPM FILE
add_executable(test_ppm_file test_ppm_file.cpp)
target_link_libraries(test_ppm_file PUBLIC ppm_file)
add_test(NAME test_ppm_file COMMAND test_ppm_file)
target_include_directories(test_ppm_file PUBLIC ${CMAKE_SOURCE_DIR}/include)

# TEST PIXEL MAP
add_executable(test_pixel test_pixel.cpp)
target_link_libraries(test_pixel PUBLIC pixel)
add_test(NAME test_pixel COMMAND test_pixel)
target_include_directories(test_pixel PUBLIC ${CMAKE_SOURCE_DIR}/include)


# TEST PIXEL MAP
add_executable(test_pixel_map test_pixel_map.cpp)
target_link_libraries(test_pixel_map PUBLIC pixel_map)
add_test(NAME test_pixel_map COMMAND test_pixel_map)
target_include_directories(test_pixel_map PUBLIC ${CMAKE_SOURCE_DIR}/include)

# TEST TONE MAPPING
add_executable(test_tone_mapping test_tone_mapping.cpp)
target_link_libraries(test_tone_mapping PUBLIC tone_mapping)
add_test(NAME test_tone_mapping COMMAND test_tone_mapping)
target_include_directories(test_tone_mapping PUBLIC ${CMAKE_SOURCE_DIR}/include)
