
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

add_executable(test_sphere test_sphere.cpp)
target_link_libraries(test_sphere PUBLIC sphere)
add_test(NAME test_sphere COMMAND test_sphere)
target_include_directories(test_sphere PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(test_ellipsoid test_ellipsoid.cpp)
target_link_libraries(test_ellipsoid PUBLIC ellipsoid)
add_test(NAME test_ellipsoid COMMAND test_ellipsoid)
target_include_directories(test_ellipsoid PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(test_face test_face.cpp)
target_link_libraries(test_face PUBLIC face)
add_test(NAME test_face COMMAND test_face)
target_include_directories(test_face PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(test_bounding_box test_bounding_box.cpp)
target_link_libraries(test_bounding_box PUBLIC bounding_box)
add_test(NAME test_bounding_box COMMAND test_bounding_box)
target_include_directories(test_bounding_box PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(test_cone test_cone.cpp)
target_link_libraries(test_cone PUBLIC cone)
add_test(NAME test_cone COMMAND test_cone)
target_include_directories(test_cone PUBLIC ${CMAKE_SOURCE_DIR}/include)