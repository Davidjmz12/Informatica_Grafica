
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


# TEST planet
add_executable(test_planet test_planet.cpp)
target_link_libraries(test_planet PUBLIC planet)
add_test(NAME test_planet COMMAND test_planet)
target_include_directories(test_planet PUBLIC ${CMAKE_SOURCE_DIR}/include)


# TEST PPM FILE
add_executable(test_ppm_file test_ppm_file.cpp)
target_link_libraries(test_ppm_file PUBLIC ppm_file)
add_test(NAME test_ppm_file COMMAND test_ppm_file)
target_include_directories(test_ppm_file PUBLIC ${CMAKE_SOURCE_DIR}/include)

# TEST color MAP
add_executable(test_color test_color.cpp)
target_link_libraries(test_color PUBLIC color)
add_test(NAME test_color COMMAND test_color)
target_include_directories(test_color PUBLIC ${CMAKE_SOURCE_DIR}/include)


# TEST color MAP
add_executable(test_color_map test_color_map.cpp)
target_link_libraries(test_color_map PUBLIC color_map)
add_test(NAME test_color_map COMMAND test_color_map)
target_include_directories(test_color_map PUBLIC ${CMAKE_SOURCE_DIR}/include)

# TEST TONE MAPPING
add_executable(test_tone_mapping test_tone_mapping.cpp)
target_link_libraries(test_tone_mapping PUBLIC tone_mapping)
add_test(NAME test_tone_mapping COMMAND test_tone_mapping)
target_include_directories(test_tone_mapping PUBLIC ${CMAKE_SOURCE_DIR}/include)


# TEST ELLIPSOID
add_executable(test_ellipsoid test_ellipsoid.cpp)
target_link_libraries(test_ellipsoid PUBLIC ellipsoid)
add_test(NAME test_ellipsoid COMMAND test_ellipsoid)
target_include_directories(test_ellipsoid PUBLIC ${CMAKE_SOURCE_DIR}/include)
