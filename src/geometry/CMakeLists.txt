
# Libraries
add_library(geometry geometry.cpp)
target_link_libraries(geometry PUBLIC intersection ray geometric)

add_library(plane plane.cpp)
target_link_libraries(plane PUBLIC geometry)

add_library(sphere sphere.cpp)
target_link_libraries(sphere PUBLIC geometry)


target_include_directories(geometry PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(geometry PUBLIC ${CMAKE_SOURCE_DIR}/include/geometry)

target_include_directories(plane PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(plane PUBLIC ${CMAKE_SOURCE_DIR}/geometry)

target_include_directories(sphere PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(sphere PUBLIC ${CMAKE_SOURCE_DIR}/geometry)