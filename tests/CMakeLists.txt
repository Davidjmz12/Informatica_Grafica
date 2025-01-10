
add_subdirectory(geometry_tests)

# TEST SPATIAL ELEMENT
add_executable(test_spatial_element test_spatial_element.cpp)
target_link_libraries(test_spatial_element PUBLIC spatial_element vector point)
add_test(NAME test_spatial_element COMMAND test_spatial_element)
target_include_directories(test_spatial_element PUBLIC ${CMAKE_SOURCE_DIR}/include)

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

# TEST PPM FILE
add_executable(test_ppm_file test_ppm_file.cpp)
target_link_libraries(test_ppm_file PUBLIC ppm_file)
add_test(NAME test_ppm_file COMMAND test_ppm_file)
target_include_directories(test_ppm_file PUBLIC ${CMAKE_SOURCE_DIR}/include)

