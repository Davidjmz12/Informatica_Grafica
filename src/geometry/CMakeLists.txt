
# Libraries
add_library(geometry geometry.cpp)
target_link_libraries(geometry PUBLIC ray)

add_library(plane plane.cpp)
target_link_libraries(plane PUBLIC geometry)

add_library(sphere sphere.cpp)
target_link_libraries(sphere PUBLIC geometry)

add_library(ellipsoid ellipsoid.cpp)
target_link_libraries(ellipsoid PUBLIC geometry)

add_library(triangle triangle.cpp)
target_link_libraries(triangle PUBLIC geometry plane)

add_library(triangle_mesh triangle_mesh.cpp)
target_link_libraries(triangle_mesh PUBLIC geometry triangle)

add_library(disk disk.cpp)
target_link_libraries(disk PUBLIC plane)

add_library(box box.cpp)
target_link_libraries(box PUBLIC triangle_mesh)


target_include_directories(geometry PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(plane PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(sphere PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(ellipsoid PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(triangle PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(triangle_mesh PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(disk PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(box PUBLIC ${CMAKE_SOURCE_DIR}/include)
