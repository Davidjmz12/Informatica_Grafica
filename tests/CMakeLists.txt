
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