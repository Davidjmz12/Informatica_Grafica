
# TEST CYLINDER
add_executable(test_cylinder test_cylinder.cpp)
target_link_libraries(test_cylinder PUBLIC cylinder disk)
add_test(NAME test_cylinder COMMAND test_cylinder)
target_include_directories(test_cylinder PUBLIC ${CMAKE_SOURCE_DIR}/include)

# TEST DISK
add_executable(test_disk test_disk.cpp)
target_link_libraries(test_disk PUBLIC disk)
add_test(NAME test_disk COMMAND test_disk)
target_include_directories(test_disk PUBLIC ${CMAKE_SOURCE_DIR}/include)

# TEST PLANE
add_executable(test_plane test_plane.cpp)
target_link_libraries(test_plane PUBLIC plane)
add_test(NAME test_plane COMMAND test_plane)
target_include_directories(test_plane PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(test_triangle test_triangle.cpp)
target_link_libraries(test_triangle PUBLIC triangle)
add_test(NAME test_triangle COMMAND test_triangle)
target_include_directories(test_triangle PUBLIC ${CMAKE_SOURCE_DIR}/include)


