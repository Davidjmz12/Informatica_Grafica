add_subdirectory(kd-trees)
# Geometry header
add_library(geometry INTERFACE)
target_link_libraries(geometry INTERFACE intersection_object ray ellipsoid sphere triangle mesh cylinder disk box plane face brdf cone)


add_library(ellipsoid ellipsoid.cpp)
target_link_libraries(ellipsoid PUBLIC geometry)

add_library(sphere sphere.cpp)
target_link_libraries(sphere PUBLIC geometry ellipsoid)

add_library(triangle triangle.cpp)
target_link_libraries(triangle PUBLIC geometry plane)

add_library(mesh mesh.cpp)
target_link_libraries(mesh PUBLIC geometry bounding_box kd-tree)

add_library(cylinder cylinder.cpp)
target_link_libraries(cylinder PUBLIC geometry)

add_library(disk disk.cpp)
target_link_libraries(disk PUBLIC plane)

add_library(box box.cpp)
target_link_libraries(box PUBLIC mesh)

add_library(plane plane.cpp)
target_link_libraries(plane PUBLIC geometry)

add_library(face face.cpp)
target_link_libraries(face PUBLIC geometry)

add_library(bounding_box bounding_box.cpp)
target_link_libraries(bounding_box PUBLIC spectral_color ray)

add_library(cone cone.cpp)
target_link_libraries(cone PUBLIC disk linear_map)

target_include_directories(sphere PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(ellipsoid PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(triangle PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(mesh PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(cylinder PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(disk PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(box PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(plane PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(face PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(bounding_box PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(cone PUBLIC ${CMAKE_SOURCE_DIR}/include)
