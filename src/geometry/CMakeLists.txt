# Libraries
add_library(geometry geometry.cpp)
target_link_libraries(geometry PUBLIC ray)

add_library(sphere sphere.cpp)
target_link_libraries(sphere PUBLIC geometry)

add_library(ellipsoid ellipsoid.cpp)
target_link_libraries(ellipsoid PUBLIC geometry)


target_include_directories(geometry PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(sphere PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(ellipsoid PUBLIC ${CMAKE_SOURCE_DIR}/include)
